#include "../include/battle_visitor.h"
#include "../include/observer.h" 


void BattleVisitor::notify_observers(const std::string& killer_type, const std::string& killer_name,
                                     const std::string& victim_type, const std::string& victim_name) {
    std::string event = killer_type + " (" + killer_name + ") killed " + victim_type + " (" + victim_name + ")";
    for (const auto& obs : observers_) {
        obs->update(event);
    }
}



void BattleVisitor::visit(Knight& self, std::shared_ptr<NPC> other) {
    bool self_killed = false;
    bool other_killed = false;

    if (other->get_type() == "Dragon") {
        other->set_dead();
        notify_observers(self.get_type(), self.get_name(), other->get_type(), other->get_name());
    } 
    else if (other->get_type() == "Dragon") {
        self_killed = true;
    }
    else if (other->get_type() == "Elf") {
        self_killed = true;
    } 
    
    if (other->get_type() == "Dragon") {
        self.set_dead();
        notify_observers(other->get_type(), other->get_name(), self.get_type(), self.get_name());
        return;
    }
    if (other->get_type() == "Elf") {
        self.set_dead();
        notify_observers(other->get_type(), other->get_name(), self.get_type(), self.get_name());
        return;
    }
    
    if (other->get_type() == "Dragon") {
        other->set_dead();
        notify_observers(self.get_type(), self.get_name(), other->get_type(), other->get_name());
        self.set_dead(); 
        notify_observers(other->get_type(), other->get_name(), self.get_type(), self.get_name());
        return;
    }
}

void BattleVisitor::visit(Elf& self, std::shared_ptr<NPC> other) {
    if (other->get_type() == "Dragon") {
        self.set_dead();
        notify_observers(other->get_type(), other->get_name(), self.get_type(), self.get_name());
        return;
    }
    if (other->get_type() == "Knight") {
        other->set_dead();
        notify_observers(self.get_type(), self.get_name(), other->get_type(), other->get_name());
        return;
    }
}

void BattleVisitor::visit(Dragon& self, std::shared_ptr<NPC> other) {
    other->set_dead();
    notify_observers(self.get_type(), self.get_name(), other->get_type(), other->get_name());

    if (other->get_type() == "Knight") {
        self.set_dead();
        notify_observers(other->get_type(), other->get_name(), self.get_type(), self.get_name());
    } 
    else if (other->get_type() == "Dragon") {
        self.set_dead();
        notify_observers(other->get_type(), other->get_name(), self.get_type(), self.get_name());
    }
}
