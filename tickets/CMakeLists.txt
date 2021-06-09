cmake_minimum_required(VERSION 3.19)
project(tickets)

set(CMAKE_CXX_STANDARD 11)

add_executable(tickets main.cpp ticket/ticket.cpp ticket/ticket.h ticket/numberTicket.h consts.h ticket/numberTicketStat.h ticket/numberTicket.cpp)