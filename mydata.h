#ifndef MYDATA_H
#define MYDATA_H

#include <QString>


struct my_data
{
    QString m_client_id = "d17116adf3974250b43d3ae6f9bed1f8";
    double m_set_1_range_low = 0;
    double m_set_1_range_high = 20;
    double m_set_2_range_low = 0;
    double m_set_2_range_high = 20;
    double m_set_3_range_low = 0;
    double m_set_3_range_high = 20;

    double m_topic_1_threshold = 10;
    double m_topic_2_threshold = 10;
    double m_topic_3_threshold = 10;

    my_data& operator=(const my_data& other)
    {
        m_client_id = other.m_client_id;

        m_set_1_range_low = other.m_set_1_range_low;
        m_set_1_range_high = other.m_set_1_range_high;
        m_set_2_range_low = other.m_set_2_range_low;
        m_set_2_range_high = other.m_set_2_range_high;
        m_set_3_range_low = other.m_set_3_range_low;
        m_set_3_range_high = other.m_set_3_range_high;

        m_topic_1_threshold = other.m_topic_1_threshold;
        m_topic_2_threshold = other.m_topic_2_threshold;
        m_topic_3_threshold = other.m_topic_3_threshold;

        return *this;
    }
};

#endif // MYDATA_H
