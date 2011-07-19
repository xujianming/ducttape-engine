
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#include "Root.hpp"

#include "utils/Logger.hpp"

#include "event/Event.hpp"
#include "event/EventListener.hpp"
#include "event/EventBinding.hpp"

class TestTriggerEvent : public dt::Event {
public:
    const std::string GetType() const  {
        return "testtriggerevent";
    }

    std::shared_ptr<Event> Clone() const {
        std::shared_ptr<Event> ptr(new TestTriggerEvent());
        return ptr;
    }
};

class TestBoundEvent : public dt::Event {
public:
    TestBoundEvent(int data) {
        mData = data;
    }

    const std::string GetType() const  {
        return "testboundevent";
    }

    std::shared_ptr<Event> Clone() const {
        std::shared_ptr<Event> ptr(new TestBoundEvent(mData));
        return ptr;
    }

    int mData;
};

class TestEventListener : public dt::EventListener {
public:
    void HandleEvent(std::shared_ptr<dt::Event> e) {
        std::cout << "Received: " << e->GetType() << std::endl;
        if(e->GetType() == "testtriggerevent") {
            mHasReceivedTriggerEvent = true;
        } else if(e->GetType() == "testboundevent") {
            if(std::dynamic_pointer_cast<TestBoundEvent>(e)->mData == 42) {
                mHasReceivedBoundEvent = true;
            } else {
                std::cerr << "The data has not been transfered correctly." << std::endl;
                exit(1);
            }
        }
    }

    bool mHasReceivedTriggerEvent;
    bool mHasReceivedBoundEvent;
};

int main(int argc, char** argv) {
    dt::Root& root = dt::Root::get_mutable_instance();
    root.Initialize(argc, argv);

    root.GetStringManager()->Add("testtriggerevent");
    root.GetStringManager()->Add("testboundevent");

    TestEventListener listener;
    root.GetEventManager()->AddListener(&listener);

    dt::BindingsManager::Get()->Bind(new dt::EventBinding("testtriggerevent", new TestBoundEvent(42)));

    root.GetEventManager()->InjectEvent(new TestTriggerEvent());

    if(!listener.mHasReceivedTriggerEvent) {
        std::cerr << "The EventListener has not received the trigger event." << std::endl;
        return 1;
    }

    if(!listener.mHasReceivedBoundEvent) {
        std::cerr << "The EventListener has not received the bound event." << std::endl;
        return 1;
    }

    std::cout << "EventBindings: OK" << std::endl;
    root.Deinitialize();
    return 0;
}