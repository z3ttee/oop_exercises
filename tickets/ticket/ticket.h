//
// Created by Cedric Zitzmann on 09.06.2021.
//

#ifndef TICKETS_TICKET_H
#define TICKETS_TICKET_H

#include <string>
using namespace std;

class Ticket {

public:
    Ticket(string customerName): ticketId(++nextTicketId), customerName(customerName) {}
    virtual ~Ticket(){};
    virtual int winRank() = 0;

private:
    static int nextTicketId;

protected:
    int ticketId;
    string customerName;
};


#endif //TICKETS_TICKET_H
