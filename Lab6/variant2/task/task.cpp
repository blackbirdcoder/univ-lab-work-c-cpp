//  *************************
//  * Laboratory work 6     *
//  * Variant 2             *
//  *************************
//
// Task:
// Train ticket availability system

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>


struct DataRoute {
    std::string routeNumber;
    std::string route;
    std::string departureTime;
    std::string arrivalTime;
};

DataRoute data[] = {
        {"1","Boston - Dallas","13:00","22:00"},
        {"2","Boston - Detroit","8:00","16:30"},
};


class Train {
private:
    std::vector<std::string> carriage;
    std::map<std::string, std::string> routeSheet;
public:
    explicit Train(const DataRoute& obj)
    {
        routeSheet = {
                {"number", obj.routeNumber},
                {"name", obj.route},
                {"departureTime", obj.departureTime},
                {"arrivalTime", obj.arrivalTime},
        };
    };

    void build(int seatsQty)
    {
        for (int i = 0; i < seatsQty; ++i)
        {
            carriage.push_back(std::to_string(i + 1));
        }
    }

    std::vector<std::string> getCarriage()
    {
        return carriage;
    };

    void replaceCarriage(const std::string& reservationMarker, int& idx)
    {
        carriage[idx] = reservationMarker;
    }

    std::map<std::string, std::string> getRouteSheet()
    {
        return routeSheet;
    }
};

class Ticket {
private:
    std::vector<std::map<std::string, std::string>> tickets;
public:
    void addTicket(std::map<std::string, std::string>& dataTicket)
    {
        tickets.push_back(dataTicket);
    }

    void showTicket()
    {
        if (!tickets.empty())
        {
            std::cout << "---- Your tickets ----" << std::endl;
            for (auto ticket : tickets)
            {
                std::cout << "********** Ticket ************" << std::endl;
                std::cout << "Train number: " << ticket["number"] << std::endl;
                std::cout << "Route: " << ticket["name"] << std::endl;
                std::cout << "Time:" << ticket["departureTime"] << " - " << ticket["arrivalTime"] << std::endl;
                std::cout << "Seat number: " << ticket["seat"] << std::endl;
                std::cout << "*******************************" << std::endl;
            }
        }
        else
        {
            std::cout << "You don't have tickets" << std::endl;
        }
    }
};


class Terminal {
private:
    const std::string  markerBusy = "X";
    std::vector<int> busy;

public:
    void showScheduleBoard(std::vector<Train>& trains)
    {
        std::cout << "---------------- Schedule Board ----------------" << std::endl;
        std::cout << "Train:\tRoute:\t\t\tDep:\tArr:" << std::endl;
        for (auto& refTrain : trains)
        {
            std::map<std::string, std::string> sheet = refTrain.getRouteSheet();
            std::cout << sheet["number"] + "\t"
            << sheet["name"] + " " + "\t"
            << sheet["departureTime"] + "\t"
            << sheet["arrivalTime"] << std::endl;
        }
        std::cout << "------------------------------------------------" << std::endl;
    }
    std::vector<std::string> getCarriage(std::vector<Train>& refTrains, char& refTrainNum)
    {
        std::vector<std::string> carriageData;
        bool passengerSeatStatus = false;
        for(auto curTrain : refTrains)
        {
            std::map<std::string, std::string> sheet = curTrain.getRouteSheet();
            if (sheet["number"] == std::string(1, refTrainNum))
            {
                std::cout << sheet["name"] << std::endl;
                std::vector<std::string> carriage = curTrain.getCarriage();
                for (auto& curCarriage : carriage)
                {
                    if (curCarriage != markerBusy)
                    {
                        passengerSeatStatus = true;
                        break;
                    }
                }
                if (passengerSeatStatus)
                {
                    std::cout << "Passenger seats in a carriage:" << std::endl;
                    for(auto& refCurrentCarriage: carriage)
                    {
                        carriageData.push_back(refCurrentCarriage);
                        std::cout << "[" << refCurrentCarriage << "]" << " ";
                    }
                    std::cout << std::endl;
                    return carriage;
                }
                else
                {
                    std::cout << "There are no empty seats for passengers" << std::endl;
                    return carriageData;
                }
            }
        }
        std::cout << "No train with this number!" << std::endl;
        return carriageData;
    }

    auto makeTicket(std::vector<Train>& refTrains, char& refTrainNum, int num)
    {
        std::map<std::string, std::string> sheet;
        for (auto& train : refTrains)
        {
            sheet = train.getRouteSheet();
            if (sheet["number"] == std::string(1, refTrainNum))
            {
                std::vector<std::string> carriage = train.getCarriage();
                auto res = std::find(
                        carriage.begin(), carriage.end(), std::to_string(num)
                        );
                if (res != carriage.end())
                {
                    int idx = num - 1;
                    train.replaceCarriage(markerBusy, idx);
                    sheet.insert({"seat", std::to_string(num)});
                    std::cout << "You bought a passenger seat " << num << std::endl;
                    return sheet;
                }
            }
        }
        return sheet;
    }

    void busyAutoClear()
    {
        if (!busy.empty())
        {
            busy.clear();
        }
    }

    bool busyAdd(int numSeat)
    {
        auto res = std::find(busy.begin(), busy.end(), numSeat);
        if (res == busy.end())
        {
            busy.push_back(numSeat);
            return true;
        }
        return false;
    }
};

int main() {
    char answer;
    char trainNumber;
    char seatNumber;
    Ticket ticket;
    std::vector<Train> trains;
    for (const auto& item : data)
    {
        Train train(item);
        train.build(6);
        trains.push_back(train);
    }
    Terminal terminal;
    while (true)
    {
        terminal.showScheduleBoard(trains);
        std::cout << "Want to buy a train ticket? [Y/N] >";
        std::cin >> answer;
        if (toupper(answer) == 'N')
        {
            ticket.showTicket();
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        if (toupper(answer) == 'Y')
        {
            while (true)
            {
                std::cout << "Enter train number >";
                std::cin >> trainNumber;
                if (isdigit(trainNumber))
                {
                    break;
                }
            }
            std::vector<std::string> carriage = terminal.getCarriage(trains, trainNumber);
            if (!carriage.empty())
            {
                terminal.busyAutoClear();
                while (true)
                {
                    std::cout << "To exit [0] enter" << std::endl;
                    std::cout << "Enter seat number >";
                    std::cin >> seatNumber;
                    if (seatNumber == '0')
                    {
                        break;
                    }
                    auto res = std::find(
                            carriage.begin(), carriage.end(), std::string(1, seatNumber)
                            );
                    if (res != carriage.end())
                    {
                        int seat = std::stoi(std::string(1, seatNumber));
                        if (terminal.busyAdd(seat))
                        {
                            std::map<std::string, std::string> sheet = terminal.makeTicket(
                                    trains, trainNumber, seat
                                    );
                            ticket.addTicket(sheet);
                        }
                        else
                        {
                            std::cout << "Busy now!" << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "No passenger seat!" << std::endl;
                    }
                }
            }
        }
    }
    return 0;
}