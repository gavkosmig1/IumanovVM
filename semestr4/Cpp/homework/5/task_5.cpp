#include <chrono>
#include <thread>

#include "Log.h"

int main(void) {
  Log* log = Log::Instance();

  log->message(LOG_NORMAL, "Look, if you had one shot or one opportunity");
  log->message(LOG_WARNING, "To seize everything you ever wanted in one moment");
  log->message(LOG_ERROR, "Would you capture it or just let it slip?");
  std::this_thread::sleep_for(std::chrono::seconds(2));

  log->message(LOG_WARNING, "His palms are sweaty, knees weak, arms are heavy");
  log->message(LOG_NORMAL, "There's vomit on his sweater already, mom's spaghetti");
  log->message(LOG_ERROR, "He's nervous, but on the surface, he looks calm and ready");
  std::this_thread::sleep_for(std::chrono::seconds(3));

  log->message(LOG_ERROR, "To drop bombs, but he keeps on forgetting");
  log->message(LOG_WARNING, "What he wrote down, the whole crowd goes so loud");
  log->message(LOG_NORMAL, "He opens his mouth, but the words won't come out");
  std::this_thread::sleep_for(std::chrono::seconds(1));

  log->message(LOG_NORMAL, "He's chokin', how? Everybody's jokin' now");
  log->message(LOG_WARNING, "The clock's run out, time's up, over, blaow");
  log->message(LOG_ERROR, "I am gonna finnish myself!!");
  std::this_thread::sleep_for(std::chrono::seconds(4));

  log->print();

  return 0;
}