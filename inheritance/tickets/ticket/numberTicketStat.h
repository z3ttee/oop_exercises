//
// Created by Cedric Zitzmann on 09.06.2021.
//

#include "numberTicket.h"
#include <iostream>

class NumberTicketStat: public NumberTicket {

public:
    NumberTicketStat(string customerName, int number): NumberTicket(customerName, number), winRankCalls(0) {
        for(int i = 0; i < amountDigits + 1; ++i) {
            rankWon[i] = 0;
        }
    }

    ~NumberTicketStat() {
        int matchedDigits = 0;

        for(int &i : rankWon) {
            if(i != 0) {
                ++matchedDigits;
            }
        }

        cout << "Los " << ticketId << " (" << customerName << ") = "
             << number << ", " << winRankCalls << " Runden:\n";
        for (int i = 0; i <= amountDigits; ++i) {
            cout << i << ":" << rankWon[i] << " ";
        }
        cout << endl;

        /*std::cout << "\n" << customerName << " has bet " << number << " with Ticket #" << ticketId << endl;
        std::cout << customerName << " matched " << matchedDigits << " digits after " << winRankCalls << " draws\n" << endl;
        for (int i = 0; i <= amountDigits; ++i) {
            cout << i << ":" << rankWon[i] << " ";
        }*/
    }

    virtual int winRank() {
        int rank = NumberTicket::winRank();

        ++winRankCalls;
        ++rankWon[rank];

        return rank;
    }

private:
    int winRankCalls;
    int rankWon[amountDigits + 1];

};
