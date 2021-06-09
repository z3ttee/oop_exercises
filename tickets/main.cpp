#include "ctime"

#include "./ticket/ticket.h"
#include "./ticket/numberTicketStat.h"

int main() {
    srand(time(nullptr));

    Ticket *ticketOne, *ticketTwo;

    ticketOne = new NumberTicketStat("Franz", 1234);
    ticketTwo = new NumberTicketStat("Xaver", 6666);

    for(int i = 0; i < 1000000; ++i) {
        NumberTicketStat::drawNumber();

        ticketOne->winRank();
        ticketTwo->winRank();
    }

    delete ticketOne;
    delete ticketTwo;
    return 0;
}
