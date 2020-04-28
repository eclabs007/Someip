
/*
 * Function : init_communication
 * Description : Initialising SomeIP communication
 * Returns :Nothing
 * Param :void
 * Author: Athul PK
 *
 * */

#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
#include "csignal"
#endif


#include "communication.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <cluster.h>
#include <QThread>
#include <vsomeip/vsomeip.hpp>
#include <memory>
extern Cluster *cluster;
s_vehicle_data_t data;
std::shared_ptr<vsomeip::application> app;
void on_message(const std::shared_ptr<vsomeip::message> &_response) {

    std::stringstream its_message;
    its_message << "CLIENT: received a notification for event ["
            << std::setw(4) << std::setfill('0') << std::hex
            << _response->get_service() << "."
            << std::setw(4) << std::setfill('0') << std::hex
            << _response->get_instance() << "."
            << std::setw(4) << std::setfill('0') << std::hex
            << _response->get_method() << "] to Client/Session ["
            << std::setw(4) << std::setfill('0') << std::hex
            << _response->get_client() << "/"
            << std::setw(4) << std::setfill('0') << std::hex
            << _response->get_session()
            << "] = ";
    std::shared_ptr<vsomeip::payload> its_payload = _response->get_payload();
    vsomeip::length_t l = its_payload->get_length();
    its_message << "(" << std::dec << its_payload->get_length() << ") ";
    for (uint32_t i = 0; i < its_payload->get_length(); ++i)
        its_message << std::hex << std::setw(2) << std::setfill('0')
            << (int) its_payload->get_data()[i] << " ";
    std::cout << its_message.str() << std::endl;

    data.type=(int)*(its_payload->get_data());
    data.message=(int)*(its_payload->get_data()+1);

   switch(data.type){
    case TYPE_DATA_SPEED :
        cluster->setSpeed(QVariant(data.message));

        break;
    case TYPE_DATA_RPM:
        cluster->setRpm(data.message);

        break;
    case TYPE_DATA_FUEL:
        cluster->setFuel(data.message);
        break;
    case TYPE_DATA_TEMP:
         cluster->setTemp(data.message);
        break;
    case TYPE_DATA_LI:
        cluster->set_l_value(data.message);
        break;
    case TYPE_DATA_RI:
        cluster->set_r_value(data.message);
        break;
    case TYPE_DATA_UN:
        break;
    }

}



std::mutex mutex;
std::condition_variable condition;


void on_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available) {
    std::cout << "CLIENT: Service ["
            << std::setw(4) << std::setfill('0') << std::hex << _service << "." << _instance
            << "] is "
            << (_is_available ? "available." : "NOT available.")
            << std::endl;
    condition.notify_one();
}
void run() {
    std::unique_lock<std::mutex> its_lock(mutex);
    condition.wait(its_lock);

    std::set<vsomeip::eventgroup_t> its_groups;
    its_groups.insert(SAMPLE_EVENTGROUP_ID);
    app->request_event(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID, its_groups, true);
    app->subscribe(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENTGROUP_ID);

  }


void  * init_communication(void *){


   QThread::sleep(2);
   cluster->setSpeed(QVariant(0));
   cluster->setRpm(0);
   cluster->setTemp(0);
   cluster->setFuel(0);

   app = vsomeip::runtime::get()->create_application("Hello");
   app->init();
   app->register_availability_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, on_availability);
   app->request_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
   app->register_message_handler(vsomeip::ANY_SERVICE, vsomeip::ANY_INSTANCE, vsomeip::ANY_METHOD, on_message);
   std::thread sender(run);
    app->start();
}
