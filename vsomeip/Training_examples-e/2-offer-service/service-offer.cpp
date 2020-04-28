#include <vsomeip/vsomeip.hpp>

#define SAMPLE_SERVICE_ID 0x1777
#define SAMPLE_INSTANCE_ID 0x5677

std::shared_ptr< vsomeip::application > app;

int main() {

    app = vsomeip::runtime::get()->create_application("ECLABS007");
    app->init();
    app->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
    app->start();
}
