//
// Created by Cedric Zitzmann on 09.06.2021.
//

#include "ticket.h"
#include "../consts.h"

class NumberTicket: public Ticket {

public:
    NumberTicket(string customerName, int number): Ticket(customerName), number(number) {}

    virtual int winRank() {
        int tmpNumber = number;
        int tmpDrawn = numberDrawn;
        int k = 0;

        for(int i = 0; i < amountDigits; ++i) {
            if(tmpNumber % 10 == tmpDrawn % 10) {
                ++k;
            }

            tmpDrawn /= 10;
            tmpNumber /= 10;
        }

        return k;
    }

    static void drawNumber() {
        numberDrawn = rand() % (maxNumber + 1);
    }

protected:
    int number;
    static int numberDrawn;
};
