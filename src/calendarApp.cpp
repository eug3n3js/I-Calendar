#include "calendarApp.h"

bool cmp::operator()(const std::shared_ptr<Event> a, const std::shared_ptr<Event> b) const {
    return a->date() < b->date();
}

bool CalendarApp::process_request(){
    std::string user_input;
    int input;
    print_menu();
    std::cin >> user_input;
    if (std::cin.eof()){
        return true;
    }
    if (is_number(user_input)){
        input = std::stoi(user_input);
    } else {
        std::cout << "\tINCORRECT INPUT\n";
        return false;
    }
    if (input == 1){
        try{
            std::string prompt, full_prompt;
            std::cout << "\tENTER DATE OF DAY\n";
            std::cin >> prompt;
            if (std::cin.eof()){
                return true;
            }
            Parser parser = Parser(prompt);
            Time date1 = parser.parseDate();
            if (!date1.control_date()){
                throw std::logic_error(" ");
            }
            date1 += Time(0,0,1,0,0);
            std::stringstream ss;
            ss << date1;
            full_prompt = "(D=="+prompt+"|D>"+prompt+")&D<"+ss.str().substr(0, 10);
            Parser parser2 = Parser(full_prompt);
            std::shared_ptr<Expression> exp = parser2.parse();
            std::vector<std::shared_ptr<Event>> events = get_events_by_filter(exp);
            if (events.size() == 0){
                std::cout << "\tTHERE IS NO EVENTS THAT MATCHES THIS EXPRESSION\n";
            } else {
                CalendarFactory factory = CalendarFactory(events);
                std::shared_ptr<BaseCalendar> calendar = factory.make_calendar();
                calendar->print();
            }  
        } catch (std::logic_error const&) {
            std::cout << "\tINCORRECT INPUT\n";   
        }
        return false;
    } else if (input == 2){
        try{
            std::string prompt, full_prompt;
            std::cout << "\tENTER DATE OF WEEK STARTS\n";
            std::cin >> prompt;
            if (std::cin.eof()){
                return true;
            }
            Parser parser = Parser(prompt);
            Time date1 = parser.parseDate();
            if (!date1.control_date()){
                throw std::logic_error(" ");
            }
            date1 += Time(0,0,7,0,0);
            std::stringstream ss;
            ss<< date1;
            full_prompt = "(D=="+prompt+"|D>"+prompt+")&(D<"+ss.str().substr(0, 10)+")";
            Parser parser2 = Parser(full_prompt);
            std::shared_ptr<Expression> exp = parser2.parse();
            std::vector<std::shared_ptr<Event>> events = get_events_by_filter(exp);
            if (events.size() == 0){
                std::cout << "\tTHERE IS NO EVENTS THAT MATCHES THIS EXPRESSION\n";
            } else {
                CalendarFactory factory = CalendarFactory(events);
                std::shared_ptr<BaseCalendar> calendar = factory.make_calendar();
                calendar->print();
            } 
        } catch (std::logic_error const&) {
            std::cout << "\tINCORRECT INPUT\n"; 
        }
        return false;
    } else if (input == 3){
        try{
            std::string prompt, full_prompt;
            std::cout << "\tENTER DATE OF MONTH\n";
            std::cin >> prompt;
            if (std::cin.eof()){
                return true;
            }
            prompt += "-01";
            Parser parser = Parser(prompt);
            Time date1 = parser.parseDate();
            date1 += Time(0,0,30,0,0);
            std::stringstream ss;
            ss << date1;
            full_prompt = "(D=="+prompt+"|D>"+prompt+")&D<"+ss.str().substr(0, 10);
            Parser parser2 = Parser(full_prompt);
            std::shared_ptr<Expression> exp = parser2.parse();
            std::vector<std::shared_ptr<Event>> events = get_events_by_filter(exp);
            if (events.size() == 0){
                std::cout << "\tTHERE IS NO EVENTS THAT MATCHES THIS EXPRESSION\n";
            } else {
                CalendarFactory factory = CalendarFactory(events);
                std::shared_ptr<BaseCalendar> calendar = factory.make_calendar();
                calendar->print();
            }
        } catch (std::logic_error const&) {
            std::cout << "\tINCORRECT INPUT\n";
        }
        return false;
    } else if (input == 4){
        try{
            std::string prompt;
            std::cout << "\tENTER PROMPT\n";
            std::cout << "\tD - date, d - duration, P - location, M - is moveable, N - name, T - tag, A - participants\n\n";
            std::cin >> prompt;
            if (std::cin.eof()){
                return true;
            }
            Parser parser = Parser(prompt);
            std::shared_ptr<Expression> exp = parser.parse();
            std::vector<std::shared_ptr<Event>> events = get_events_by_filter(exp);
            if (events.size() == 0){
                std::cout << "\tTHERE IS NO EVENTS THAT MATCHES THIS EXPRESSION\n";
            } else {
                CalendarFactory factory = CalendarFactory(events);
                std::shared_ptr<BaseCalendar> calendar = factory.make_calendar();
                calendar->print();
            }
        
        } catch (std::logic_error const&) {
            std::cout << "\tINCORRECT EXPRESSION\n";
        }
        return false;
    } else if (input == 5){
        try{
            std::string prompt;
            std::cout << "\tENTER PROMPT\n";
            std::cout << "\tD - date, d - duration, P - location, M - is moveable, N - name, T - tag, A - participants\n\n";
            std::cin >> prompt;
            if (std::cin.eof()){
                return true;
            }
            Parser parser = Parser(prompt);
            std::shared_ptr<Expression> exp = parser.parse();
            std::vector<std::shared_ptr<Event>> events = get_events_by_filter(exp);
            for (size_t i = 0; i < events.size(); i++){
                event_list.erase(events[i]);
            }
            std::cout << "\tEVENTS WAS DELETED SUCCESSFULLY\n";
        } catch (std::logic_error const&) {
            std::cout << "\tINCORRECT INPUT\n";  
        }
        return false;
    } else if (input == 6){
        std::string file;
        std::cout << "\tENTER FILENAME\n";
        std::cin >> file;
        if (std::cin.eof()){
            return true;
        }
        try{
            CSVFileRW reader = CSVFileRW(file);
            std::vector<std::shared_ptr<Event>> events = reader.read();
            std::cout << "\tLOAD SUCCESSFUL\n";
            try{
                for (size_t i = 0; i < events.size(); i++){
                    event_list.insert(events[i]);
                    if (event_list.size() > 1){
                        if (detect_collision().size() != 0){
                            resolve_collision(detect_collision());
                        }
                    }
                }
            } catch (std::logic_error const&) {
                std::cout << "\tINCORRECT INPUT\n";
                return false;
            }
        } catch (std::logic_error const&) {
            std::cout << "\tFAILED TO LOAD\n";
            return false;
        }
    } else if (input == 7){
        try{
            std::string prompt;
            std::cout << "\tENTER PROMPT\n";
            std::cout << "\tD - date, d - duration, P - location, M - is moveable, N - name, T - tag, A - participants\n\n";
            std::cin >> prompt;
            if (std::cin.eof()){
                return true;
            }
            Parser parser = Parser(prompt);
            std::shared_ptr<Expression> exp = parser.parse();
            std::vector<std::shared_ptr<Event>> events = get_events_by_filter(exp);
            std::string file;
            std::cout << "\tENTER FILENAME\n";
            std::cin >> file;
            if (std::cin.eof()){
                return true;
            }
            CSVFileRW writer = CSVFileRW(file);
            std::vector<std::shared_ptr<Event>> out = std::vector<std::shared_ptr<Event>>(events.begin(), events.end());
            writer.write(out);
            std::cout << "\tEVENTS WAS SAVED IN FILE\n";
        } catch (std::logic_error const&) {
            std::cout << "\tFAILED TO SAVE\n";
            return false;
        }
    } else if (input == 8){
        std::string file;
        std::cout << "\tENTER FILENAME\n";
        std::cin >> file;
        if (std::cin.eof()){
            return true;
        }
        try{
            CSVFileRW writer = CSVFileRW(file);
            std::vector<std::shared_ptr<Event>> out = std::vector<std::shared_ptr<Event>>(event_list.begin(), event_list.end());
            writer.write(out);
            std::cout << "\tSAVE SUCCESSFUL\n"; 
        } catch (std::logic_error const&) {
            std::cout << "\tFAILED TO SAVE\n";
            return false;
        }
    } else if (input == 9){
        std::cout<<"\tEXITING THE CALENDAR\n";
        return true;
    } else {
        std::cout<<"\tINCORRECT INPUT\n";
    }
    return false;
}

void CalendarApp::print_menu() const {
    std::cout<<"\n\n\n\t---------------------------------------------------------\n";
    std::cout<<"\t|		 Welcome to Calendar     		|\n";
    std::cout<<"\t---------------------------------------------------------\n";							
    std::cout<<"\t|	Please choose from the following options :      |\n";
    std::cout<<"\t|	                                                |\n";
    std::cout<<"\t|	 ";
    std::cout<<"1-";
    std::cout<<"	View Activities by DAY	 	 	|\n";
    std::cout<<"\t|	 ";
    std::cout<<"2-";
    std::cout<<"	View Activities by WEEK 	 	|\n";
    std::cout<<"\t|	 ";
    std::cout<<"3-";
    std::cout<<"	View Activities by MONTH	 	|\n";
    std::cout<<"\t|	 ";
    std::cout<<"4-";
    std::cout<<"	Find Activities 	 	 	|\n";
    std::cout<<"\t|	 ";
    std::cout<<"5-";
    std::cout<<"	Remove an Activity	 	 	|\n";
    std::cout<<"\t|	 ";
    std::cout<<"6-";
    std::cout<<"	Load Activities from file	 	|\n";
    std::cout<<"\t|	 ";
    std::cout<<"7-";
    std::cout<<"	Save Activities in file by criteria 	|\n";
    std::cout<<"\t|	 ";
    std::cout<<"8-";
    std::cout<<"	Save all Activities in file	 	|\n";
    std::cout<<"\t|	 ";
    std::cout<<"9-";
    std::cout<<"	Exit	 	 		 	|\n";
    std::cout<<"\t|_______________________________________________________|\n";
    std::cout<<"\t\nOption : ";

}

bool CalendarApp::is_number(const std::string& s) const {
    auto it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

std::vector<std::shared_ptr<Event>> CalendarApp::get_events_by_filter(const std::shared_ptr<Expression> expression) const{
    std::vector<std::shared_ptr<Event>> filtered;
    for (auto it = event_list.begin(); it != event_list.end(); it++){
        if (expression->evaluate(*(it->get()))){
            filtered.push_back(*it);
        }
    }
    return filtered;
}

std::vector<std::set<std::shared_ptr<Event>, cmp>::iterator> CalendarApp::detect_collision() const {
    std::vector<std::set<std::shared_ptr<Event>, cmp>::iterator> collis;
    auto end = event_list.end();
    end--;
    for (auto it = event_list.begin(); it != end; it++){
        auto it2 = it;
        it2++;
        if (it2->get()->date() < it->get()->date() + it->get()->duration()){
            collis.push_back(it);
            break;
        }
    }
    return collis;
}

void CalendarApp::resolve_collision(std::vector<std::set<std::shared_ptr<Event>, cmp>::iterator> el){
    std::string input;
    int max_opt = 2;
    int option; 
    if (el.size() == 1){
        std::cout << "Collision detected between events: " << el[0]->get()->name() << " " << el[0]->get()->date() << std::endl;
        auto new_ = ++el[0];
        std::cout << new_->get()->name() << " " << new_->get()->date() << std::endl;
        auto bad_events = new_->get()->date() < el[0]->get()->date() ? el[0] : new_;
        std::cout << "Options: 1 - add anyway\n2 - remove " << bad_events->get()->name() << " " << bad_events->get()->date() << "\n";
        if (bad_events->get()->isMoveable()){
            std::cout << "3 - move " << bad_events->get()->name() << " " << bad_events->get()->date() << " on nearest time\n";
            max_opt = 3;
        }
        std::cout << "Option:" << std::endl;
        std::cin >> input;
        if (std::cin.eof()){
            exit(1);
        }
        if (is_number(input)){
            option = stoi(input);
        } else {
            throw std::logic_error(" ");
        }
        if (option < 1 || option > max_opt){
            throw std::logic_error(" ");
        }
        if (option == 1){
            return;
        } else if (option == 2){
            event_list.erase(*bad_events);
            return;
        } else if (option == 3) {
            int solved = 0;
            Time upperborder = el[0]->get()->date().round_day_up();
            Time lowerborder = el[0]->get()->date().round_day_up() - Time(0, 0, 1, 0, 0);
            std::set<std::shared_ptr<Event>, cmp>::iterator iter = bad_events;
            if (iter == event_list.begin()){
                iter++;
            } else {
                while (lowerborder < iter->get()->date() && iter != event_list.begin()){
                    iter--;
                }
            }
            std::shared_ptr<Event> e = *bad_events;
            event_list.erase(*bad_events);
            while (iter ->get()->date() < upperborder){
                std::set<std::shared_ptr<Event>, cmp>::iterator iter2 = iter;
                iter2++;
                if(iter2 == event_list.end()){
                    if (iter->get()->date() + iter->get()->duration() + bad_events->get()->duration() < upperborder){
                        e->set_date(iter->get()->date() + iter->get()->duration());
                        std::cout << "New date is: " << e->date() << std::endl;
                        event_list.insert(e);
                        solved = 1;
                    }
                    break;
                }
                if (iter->get()->date() + iter->get()->duration() + bad_events->get()->duration() < iter2->get()->date()){
                    e->set_date(iter->get()->date() + iter->get()->duration());
                    std::cout << "New date is: " << e->date() << std::endl;
                    event_list.insert(e);
                    solved = 1;
                    break;
                }
                iter++;
            }
            if (solved == 0){
                std::cout << "Did not found suitable time to move\n";
                return;
            }
            return;
        }
    }
}

