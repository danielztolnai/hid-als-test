#pragma once

#include <Arduino.h>
#include "HID.h"
#include "HidSensorSpec.h"

#define HID_REPORTID_AMBIENTLIGHT 110

typedef struct _ALS_FEATURE_REPORT
{
	// common properties
	//uint8_t ucReportId;
	uint8_t ucConnectionType;
	uint8_t ucReportingState;
	uint8_t ucPowerState;
	uint8_t ucSensorState;
	uint32_t ulReportInterval;

	// properties specific to this sensor
	uint16_t usIlluminanceChangeSensitivity;
	uint32_t usIlluminanceMaximum;
	uint32_t usIlluminanceMinimum;

} ALS_FEATURE_REPORT, *PALS_FEATURE_REPORT;

typedef struct _ALS_INPUT_REPORT
{
	// common values
	//uint8_t ucReportId;
	uint8_t ucSensorState;
	uint8_t ucEventType;

	// values specific to this sensor
	uint32_t usIlluminanceValue;

} ALS_INPUT_REPORT, *PALS_INPUT_REPORT;

static const uint8_t _hidMultiReportDescriptorAmbientLightSensor[] PROGMEM = {
    HID_USAGE_PAGE_SENSOR,
    HID_USAGE_SENSOR_TYPE_COLLECTION,
    HID_COLLECTION(Application),
        HID_REPORT_ID(HID_REPORTID_AMBIENTLIGHT),
	    HID_USAGE_PAGE_SENSOR,
	    HID_USAGE_SENSOR_TYPE_LIGHT_AMBIENTLIGHT,
	    HID_COLLECTION(Physical),
	        // feature reports (xmit/receive)
	        HID_USAGE_PAGE_SENSOR,

            HID_USAGE_SENSOR_PROPERTY_SENSOR_CONNECTION_TYPE, // NAry
	        HID_LOGICAL_MIN_8(0),
	        HID_LOGICAL_MAX_8(2),
	        HID_REPORT_SIZE(8),
	        HID_REPORT_COUNT(1),
	        HID_COLLECTION(Logical),
	            HID_USAGE_SENSOR_PROPERTY_CONNECTION_TYPE_PC_INTEGRATED_SEL,
	            HID_USAGE_SENSOR_PROPERTY_CONNECTION_TYPE_PC_ATTACHED_SEL,
	            HID_USAGE_SENSOR_PROPERTY_CONNECTION_TYPE_PC_EXTERNAL_SEL,
	            HID_FEATURE(Data_Arr_Abs),
	        HID_END_COLLECTION,

            HID_USAGE_SENSOR_PROPERTY_REPORTING_STATE,
	        HID_LOGICAL_MIN_8(0),
	        HID_LOGICAL_MAX_8(5),
	        HID_REPORT_SIZE(8),
	        HID_REPORT_COUNT(1),
	        HID_COLLECTION(Logical),
	            HID_USAGE_SENSOR_PROPERTY_REPORTING_STATE_NO_EVENTS_SEL,
	            HID_USAGE_SENSOR_PROPERTY_REPORTING_STATE_ALL_EVENTS_SEL,
	            HID_USAGE_SENSOR_PROPERTY_REPORTING_STATE_THRESHOLD_EVENTS_SEL,
	            HID_USAGE_SENSOR_PROPERTY_REPORTING_STATE_NO_EVENTS_WAKE_SEL,
	            HID_USAGE_SENSOR_PROPERTY_REPORTING_STATE_ALL_EVENTS_WAKE_SEL,
	            HID_USAGE_SENSOR_PROPERTY_REPORTING_STATE_THRESHOLD_EVENTS_WAKE_SEL,
	            HID_FEATURE(Data_Arr_Abs),
	        HID_END_COLLECTION,

            HID_USAGE_SENSOR_PROPERTY_POWER_STATE,
	        HID_LOGICAL_MIN_8(0),
	        HID_LOGICAL_MAX_8(5),
	        HID_REPORT_SIZE(8),
	        HID_REPORT_COUNT(1),
	        HID_COLLECTION(Logical),
	            HID_USAGE_SENSOR_PROPERTY_POWER_STATE_UNDEFINED_SEL,
	            HID_USAGE_SENSOR_PROPERTY_POWER_STATE_D0_FULL_POWER_SEL,
	            HID_USAGE_SENSOR_PROPERTY_POWER_STATE_D1_LOW_POWER_SEL,
	            HID_USAGE_SENSOR_PROPERTY_POWER_STATE_D2_STANDBY_WITH_WAKE_SEL,
	            HID_USAGE_SENSOR_PROPERTY_POWER_STATE_D3_SLEEP_WITH_WAKE_SEL,
	            HID_USAGE_SENSOR_PROPERTY_POWER_STATE_D4_POWER_OFF_SEL,
	            HID_FEATURE(Data_Arr_Abs),
	        HID_END_COLLECTION,

            HID_USAGE_SENSOR_STATE,
	        HID_LOGICAL_MIN_8(0),
	        HID_LOGICAL_MAX_8(6),
	        HID_REPORT_SIZE(8),
	        HID_REPORT_COUNT(1),
	        HID_COLLECTION(Logical),
	            HID_USAGE_SENSOR_STATE_UNKNOWN_SEL,
	            HID_USAGE_SENSOR_STATE_READY_SEL,
	            HID_USAGE_SENSOR_STATE_NOT_AVAILABLE_SEL,
	            HID_USAGE_SENSOR_STATE_NO_DATA_SEL,
	            HID_USAGE_SENSOR_STATE_INITIALIZING_SEL,
	            HID_USAGE_SENSOR_STATE_ACCESS_DENIED_SEL,
	            HID_USAGE_SENSOR_STATE_ERROR_SEL,
	            HID_FEATURE(Data_Arr_Abs),
	        HID_END_COLLECTION,

            HID_USAGE_SENSOR_PROPERTY_REPORT_INTERVAL,
	        HID_LOGICAL_MIN_8(0),
	        HID_LOGICAL_MAX_32(0xFF, 0xFF, 0xFF, 0xFF),
	        HID_REPORT_SIZE(32),
	        HID_REPORT_COUNT(1),
	        HID_UNIT_EXPONENT(0),
	        HID_FEATURE(Data_Var_Abs),

	        HID_USAGE_SENSOR_DATA(HID_USAGE_SENSOR_DATA_LIGHT_ILLUMINANCE, HID_USAGE_SENSOR_DATA_MOD_CHANGE_SENSITIVITY_REL_PCT),
	        HID_LOGICAL_MIN_8(0),
	        HID_LOGICAL_MAX_16(0x10, 0x27), // 10000 = 0.00 to 100.00 percent with 2 digits past decimal point
	        HID_REPORT_SIZE(16),
	        HID_REPORT_COUNT(1),
	        HID_UNIT_EXPONENT(0x0E), // scale default unit to provide 2 digits past decimal point
	        HID_FEATURE(Data_Var_Abs),

	        HID_USAGE_SENSOR_DATA(HID_USAGE_SENSOR_DATA_LIGHT_ILLUMINANCE, HID_USAGE_SENSOR_DATA_MOD_MAX),
	        HID_LOGICAL_MIN_8(0),
	        HID_LOGICAL_MAX_32(0xFF, 0xFF, 0xFF, 0xFF),
	        HID_REPORT_SIZE(32),
	        HID_REPORT_COUNT(1),
	        HID_UNIT_EXPONENT(0x0F), // scale default unit to provide 1 digit past decimal point
	        HID_FEATURE(Data_Var_Abs),

	        HID_USAGE_SENSOR_DATA(HID_USAGE_SENSOR_DATA_LIGHT_ILLUMINANCE, HID_USAGE_SENSOR_DATA_MOD_MIN),
	        HID_LOGICAL_MIN_8(0),
	        HID_LOGICAL_MAX_32(0xFF, 0xFF, 0xFF, 0xFF),
	        HID_REPORT_SIZE(32),
	        HID_REPORT_COUNT(1),
	        HID_UNIT_EXPONENT(0x0F), // scale default unit to provide 1 digit past decimal point
	        HID_FEATURE(Data_Var_Abs),

	        // input reports (transmit)
	        HID_USAGE_PAGE_SENSOR,

	        HID_USAGE_SENSOR_STATE,
	        HID_LOGICAL_MIN_8(0),
	        HID_LOGICAL_MAX_8(6),
	        HID_REPORT_SIZE(8),
	        HID_REPORT_COUNT(1),
	        HID_COLLECTION(Logical),
                HID_USAGE_SENSOR_STATE_UNKNOWN_SEL,
                HID_USAGE_SENSOR_STATE_READY_SEL,
                HID_USAGE_SENSOR_STATE_NOT_AVAILABLE_SEL,
                HID_USAGE_SENSOR_STATE_NO_DATA_SEL,
                HID_USAGE_SENSOR_STATE_INITIALIZING_SEL,
                HID_USAGE_SENSOR_STATE_ACCESS_DENIED_SEL,
                HID_USAGE_SENSOR_STATE_ERROR_SEL,
                HID_INPUT(Data_Arr_Abs),
            HID_END_COLLECTION,

            HID_USAGE_SENSOR_EVENT,
            HID_LOGICAL_MIN_8(0),
            HID_LOGICAL_MAX_8(5),
            HID_REPORT_SIZE(8),
            HID_REPORT_COUNT(1),
            HID_COLLECTION(Logical),
                HID_USAGE_SENSOR_EVENT_UNKNOWN_SEL,
                HID_USAGE_SENSOR_EVENT_STATE_CHANGED_SEL,
                HID_USAGE_SENSOR_EVENT_PROPERTY_CHANGED_SEL,
                HID_USAGE_SENSOR_EVENT_DATA_UPDATED_SEL,
                HID_USAGE_SENSOR_EVENT_POLL_RESPONSE_SEL,
                HID_USAGE_SENSOR_EVENT_CHANGE_SENSITIVITY_SEL,
                HID_INPUT(Data_Arr_Abs),
            HID_END_COLLECTION,

            HID_USAGE_SENSOR_DATA_LIGHT_ILLUMINANCE,
            HID_LOGICAL_MIN_8(0),
            HID_LOGICAL_MAX_32(0xFF, 0xFF, 0xFF, 0xFF),
            HID_UNIT_EXPONENT(0x0F), // scale default unit to provide 1 digit past decimal point
            HID_REPORT_SIZE(32),
            HID_REPORT_COUNT(1),
            HID_INPUT(Data_Var_Abs),

        HID_END_COLLECTION,
    HID_END_COLLECTION,
};

class AmbientLightSensor
{
public:
	inline AmbientLightSensor(void) {
        static HIDSubDescriptor node(_hidMultiReportDescriptorAmbientLightSensor, sizeof(_hidMultiReportDescriptorAmbientLightSensor));
	    HID().AppendDescriptor(&node);
    }

	inline void begin(void) {}

	inline void end(void) {}

	inline void update(uint32_t value) {
		this->ready = true;
		this->illuminance_value = value;
	}

	inline void handle() {
		auto time = millis();

		if (!this->ready || (this->last_update + this->update_interval > time)) {
			return;
		}

		this->last_update = time;
		this->report();
	}

protected:
	uint32_t illuminance_value = 0;
	unsigned long last_update = 0;
	const unsigned long update_interval = 100;
	bool ready = false;

	inline void SendReport(void* data, int length) {
        HID().SendReport(HID_REPORTID_AMBIENTLIGHT, data, length);
    };

	inline void report() {
        ALS_INPUT_REPORT report;
        report.ucSensorState = HID_USAGE_SENSOR_STATE_READY_SEL_ENUM;
        report.ucEventType = HID_USAGE_SENSOR_EVENT_DATA_UPDATED_SEL_ENUM;
        report.usIlluminanceValue = this->illuminance_value;

        this->SendReport(&report, sizeof(report));
    }
};
