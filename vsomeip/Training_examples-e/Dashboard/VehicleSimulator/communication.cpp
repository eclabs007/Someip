#include "communication.h"
/*
 * Function : init_communication
 * Description : Initialising SomeIP communication
 * Returns :Nothing
 * Param :void
 * Author: Athul PK
 *
 * */

#include <iomanip>
#include <iostream>
#include <sstream>

#include <condition_variable>
#include <thread>

#include <vsomeip/vsomeip.hpp>
#include "communication.h"


std::shared_ptr< vsomeip::application > app;
std::mutex mutex;
std::condition_variable condition;

void send_data(s_vehicle_data_t data) {

  std::shared_ptr< vsomeip::payload > its_payload = vsomeip::runtime::get()->create_payload();
  std::vector< vsomeip::byte_t > its_payload_data;
  its_payload_data.push_back(data.type);
   its_payload_data.push_back(data.message);
  its_payload->set_data(its_payload_data);
  app->notify(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID, its_payload);

}

void on_message(const std::shared_ptr<vsomeip::message> &_response) {

  std::shared_ptr<vsomeip::payload> its_payload = _response->get_payload();
  vsomeip::length_t l = its_payload->get_length();

  // Get payload
  std::stringstream ss;
  for (vsomeip::length_t i=0; i<l; i++) {
     ss << std::setw(2) << std::setfill('0') << std::hex
        << (int)*(its_payload->get_data()+i) << " ";
  }

  std::cout << "Service: Received message with Client/Session ["
      << std::setw(4) << std::setfill('0') << std::hex << _response->get_client() << "/"
      << std::setw(4) << std::setfill('0') << std::hex << _response->get_session() << "] "
      << ss.str() << std::endl;
}



void  * init_communication(void *) {


    app = vsomeip::runtime::get()->create_application("ECU");
    app->init();
    app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, on_message);
       app->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
       std::set<vsomeip::eventgroup_t> its_groups;
       its_groups.insert(SAMPLE_EVENTGROUP_ID);
       app->offer_event(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID, its_groups, true);
       app->start();




}
