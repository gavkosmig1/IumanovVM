#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>
#include <thread>
#include <chrono>

class SerialPort {
public:
    SerialPort(const std::string& port, int baud_rate) : port_(port), baud_rate_(baud_rate) {
        // Открываем последовательный порт
        fd_ = open(port_.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
        if (fd_ == -1) {
            std::cerr << "Ошибка открытия последовательного порта" << std::endl;
            return;
        }

        // Настройка параметров порта
        struct termios tty;
        memset(&tty, 0, sizeof tty);
        if (tcgetattr(fd_, &tty) != 0) {
            std::cerr << "Ошибка получения атрибутов последовательного порта" << std::endl;
            return;
        }

        // Устанавливаем скорость передачи данных
        cfsetospeed(&tty, baud_rate_);
        cfsetispeed(&tty, baud_rate_);

        tty.c_cflag &= ~PARENB; // Без контроля четности
        tty.c_cflag &= ~CSTOPB; // 1 стоповый бит
        tty.c_cflag &= ~CSIZE;
        tty.c_cflag |= CS8; // 8 бит данных
        tty.c_cflag &= ~CRTSCTS; // Без аппаратного управления потоком
        tty.c_cflag |= CREAD | CLOCAL; // Включаем чтение и игнорируем управляющие линии

        tty.c_lflag &= ~ICANON; // Неканонический режим
        tty.c_lflag &= ~ECHO; // Отключаем эхо
        tty.c_lflag &= ~ECHOE; // Отключаем стирание
        tty.c_lflag &= ~ECHONL; // Отключаем эхо новой строки
        tty.c_lflag &= ~ISIG; // Отключаем обработку сигналов INTR, QUIT и SUSP

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Отключаем программное управление потоком
        tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); // Отключаем специальную обработку входящих данных

        tty.c_oflag &= ~OPOST; // Отключаем специальную интерпретацию выходных данных
        tty.c_oflag &= ~ONLCR; // Отключаем преобразование новой строки в возврат каретки/перевод строки

        tty.c_cc[VTIME] = 10; // Ожидание до 1 секунды (10 децисекунд) перед возвратом, если данные не получены
        tty.c_cc[VMIN] = 0;

        // Применяем настройки
        if (tcsetattr(fd_, TCSANOW, &tty) != 0) {
            std::cerr << "Ошибка установки атрибутов последовательного порта" << std::endl;
            return;
        }
    }

    ~SerialPort() {
        // Закрываем порт при уничтожении объекта
        if (fd_ != -1) {
            close(fd_);
        }
    }

    // Метод для отправки команды
    bool sendCommand(const std::string& command) {
        if (fd_ == -1) {
            return false;
        }

        // Записываем команду в порт
        int n = write(fd_, command.c_str(), command.length());
        if (n < 0) {
            std::cerr << "Ошибка записи в последовательный порт" << std::endl;
            return false;
        }

        return true;
    }

    // Метод для чтения ответа
    std::string readResponse() {
        if (fd_ == -1) {
            return "";
        }

        // Читаем данные из порта
        char buffer[256];
        int n = read(fd_, buffer, sizeof(buffer));
        if (n < 0) {
            std::cerr << "Ошибка чтения из последовательного порта" << std::endl;
            return "";
        }

        return std::string(buffer, n);
    }

private:
    std::string port_; // Имя порта
    int baud_rate_; // Скорость передачи данных
    int fd_; // Файловый дескриптор порта
};

int main() {
    std::string port = "/dev/ttyS0"; // Замените на нужный порт
    int baud_rate = B115200; // Скорость 115200 бод

    // Создаем объект для работы с последовательным портом
    SerialPort serialPort(port, baud_rate);

    // Основной цикл программы
    while (true) {
        int angle;
        std::cout << "Введите угол поворота (0-180): ";
        std::cin >> angle;

        // Проверка корректности введенного угла
        if (angle < 0 || angle > 180) {
            std::cerr << "Угол должен быть в диапазоне от 0 до 180!" << std::endl;
            continue;
        }

        // Форматируем команду в виде "Sxxx"
        char command[6];
        snprintf(command, sizeof(command), "S%03d", angle);

        // Отправляем команду и читаем ответ
        if (serialPort.sendCommand(command)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(20)); // Задержка для соблюдения частоты 50 Гц
            std::string response = serialPort.readResponse();
            std::cout << "Ответ: " << response << std::endl;
        } else {
            std::cerr << "Ошибка отправки команды" << std::endl;
        }

        // Запрос на продолжение работы
        std::cout << "Продолжить? (y/n): ";
        char choice;
        std::cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            break;
        }
    }

    return 0;
}
