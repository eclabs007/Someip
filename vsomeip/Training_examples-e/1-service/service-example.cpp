#include <vsomeip/vsomeip.hpp>

std::shared_ptr< vsomeip::application > app;

int main() {

    app = vsomeip::runtime::get()->create_application("ECLABS007");
    app->init();
    app->start();
}
