#include "God.hh"

bool God::doYouAuthorizeThisMyLord() {
  int imAFeelingGoodToday                       = rand() % 2;
  int repeatMeThatIAmTheBestUntilITellYouToStop = rand() % 10;
  int justKiddingButTellMeAgain                 = rand() % 42 + 12;
  int doItAgainMotherFu                         = 0;
  while (repeatMeThatIAmTheBestUntilITellYouToStop != 7) {
    doItAgainMotherFu++;
    repeatMeThatIAmTheBestUntilITellYouToStop = rand() % 10;
  }
  justKiddingButTellMeAgain /= doItAgainMotherFu + 1;
  return imAFeelingGoodToday == (justKiddingButTellMeAgain > repeatMeThatIAmTheBestUntilITellYouToStop);
}
