#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QDebug>

#define SAMPLE_SERVICE_ID       0x1234
#define SAMPLE_INSTANCE_ID      0x5678
#define SAMPLE_METHOD_ID        0x0421

#define SAMPLE_EVENT_ID         0x8778
#define SAMPLE_GET_METHOD_ID    0x0001
#define SAMPLE_SET_METHOD_ID    0x0002

#define SAMPLE_EVENTGROUP_ID    0x4465

#define OTHER_SAMPLE_SERVICE_ID 0x0248
#define OTHER_SAMPLE_INSTANCE_ID 0x5422
#define OTHER_SAMPLE_METHOD_ID  0x1421

void  * init_communication(void *);
typedef enum {
    TYPE_DATA_SPEED,
    TYPE_DATA_RPM,
     TYPE_DATA_FUEL,
     TYPE_DATA_TEMP,
     TYPE_DATA_LI,
     TYPE_DATA_RI,
     TYPE_DATA_UN
}method_t;
typedef struct s_vehicle_data{
    char type;
    int message;

}s_vehicle_data_t;

#endif // COMMUNICATION_H
