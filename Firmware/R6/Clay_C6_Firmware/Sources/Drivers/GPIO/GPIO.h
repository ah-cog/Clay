#ifndef GPIO_H
#define GPIO_H

#include "PE_Types.h"
#include "PE_LDD.h"

////Includes //////////////////////////////////////////////////////
#include "PE_Types.h"

////Macros ////////////////////////////////////////////////////////
//#define CHANNEL_COUNT 12

#define CHANNEL_ENABLED  1
#define CHANNEL_DISABLED 0

//#define CHANNEL_DIRECTION_OUTPUT 0
//#define CHANNEL_DIRECTION_INPUT  1

//#define CHANNEL_MODE_TOGGLE   1
//#define CHANNEL_MODE_WAVEFORM 2
//#define CHANNEL_MODE_PULSE    3

#define CHANNEL_VALUE_TOGGLE_ON  1
#define CHANNEL_VALUE_TOGGLE_OFF 0

////Typedefs  /////////////////////////////////////////////////////
typedef enum {
	CHANNEL_1 = 0,
	CHANNEL_2 = 1,
	CHANNEL_3 = 2,
	CHANNEL_4 = 3,
	CHANNEL_5 = 4,
	CHANNEL_6 = 5,
	CHANNEL_7 = 6,
	CHANNEL_8 = 7,
	CHANNEL_9 = 8,
	CHANNEL_10 = 9,
	CHANNEL_11 = 10,
	CHANNEL_12 = 11,
	CHANNEL_COUNT
} Channel_Number;

typedef enum {
	CHANNEL_DIRECTION_OUTPUT = 0,     // i.e., source: Clay, destination: world
	CHANNEL_DIRECTION_INPUT = 1,     // i.e., source: world, destination: Clay
	CHANNEL_DIRECTION_COUNT
} Channel_Direction;

typedef enum {
	CHANNEL_TYPE_TOGGLE = 1,
	CHANNEL_TYPE_WAVEFORM = 2,
	CHANNEL_TYPE_PULSE = 4,
	CHANNEL_TYPE_COUNT
} Channel_Type;

typedef enum {
	MCU_GPIO_PORT_PTB,
	MCU_GPIO_PORT_PTC,
	MCU_GPIO_PORT_PTD,
	MCU_GPIO_PORT_PTE,
	MCU_GPIO_PORT_COUNT
} MCU_GPIO_Port;

typedef enum {
	MCU_ADC0, MCU_ADC1, MCU_ADC_COUNT
} MCU_ADC_Channel;

typedef enum {
	MCU_PWM_OUT_1, MCU_PWM_OUT_2, MCU_PWM_OUT_3, MCU_PWM_OUT_4, MCU_PULSE_COUNT
} MCU_PWM_Channel;

typedef struct {
	MCU_GPIO_Port port;
	uint32_t mask;
} MCU_GPIO_Digital_Interface;

typedef struct {
	MCU_ADC_Channel adc_channel;
	uint32_t sample_group;
} MCU_GPIO_ADC_Interface;

typedef struct {
	MCU_PWM_Channel pwm_channel;
} MCU_GPIO_PWM_Interface;

typedef struct {
	uint32_t supported_interfaces;
	MCU_GPIO_Digital_Interface * digital_interface;
	MCU_GPIO_ADC_Interface * adc_interface;
	MCU_GPIO_PWM_Interface * pwm_interface;
} MCU_GPIO_Profile;

/*
typedef struct {
	void *key;

	// function: add_key(const char* key, <function pointer to generate or get data>)

	// - pointer to "get data" function for node
	// - pointer to "update data" function for node

	// Value types:
	// - constant (entered/selected by user)
	// - value from a hardware input resource (e.g., ADC input, digital input)
	// - value from another Clay device
	// - mathematical function
	// - remote data source (e.g., HTTP)

} Data_Entry; // Data_Graph_Node; // i.e., key in (key,value) store
*/

// TODO: CONTENT_TYPE: INTEGER, DECIMAL, BINARY, TEXT, FUNCTION, ...
#define CONTENT_TYPE_CHAR   1
#define CONTENT_TYPE_INT16  2
#define CONTENT_TYPE_INT32  3
#define CONTENT_TYPE_FLOAT  4
#define CONTENT_TYPE_DOUBLE 5

// Prototypes
struct Propagator;

typedef struct Observable {
	char *device_uuid;
	char *provider_uuid;

	char *key;
	int8_t content_type;
	void *content;

	struct Propagator *propagators;

	// TODO: USE_LINKED_LIST(Observable): a define to add linked list functionality to the structure
	struct Observable *previous;
	struct Observable *next;
} Observable;

extern Observable* Create_Observable (const char *key, int8_t content_type, void *content);
extern void Set_Observable_Device_UUID (Observable *observable, char *device_uuid);
extern void Set_Observable_Provider_UUID (Observable *observable, char *provider_uuid);
extern void Set_Observable_Content (Observable *observable, int8_t content_type, void *content);
extern int8_t Get_Observable_Type (Observable *observable);
// TODO: extern Content_Entry Get_Observable_Data (Observable *observable); --or-- extern Content_Entry Get_Observable_Data (Observable *observable, int8_t content_type);
extern int16_t Get_Observable_Data_Int16 (Observable *observable);
extern int32_t Get_Observable_Data_Int32 (Observable *observable);
extern float Get_Observable_Data_Float (Observable *observable);
extern double Get_Observable_Data_Double (Observable *observable);
extern void Delete_Observable (Observable *observable);

// TODO: (?) Consider adding function pointer to support custom function definition in propagator.
typedef struct Propagator { // rename to "Ripple"
	Observable *source;
	Observable *destination;

	struct Propagator *previous;
	struct Propagator *next;
} Propagator;

extern Propagator* Create_Propagator (Observable *source, char *source_key, Observable *destination, char *destination_key);
extern void Delete_Propagator ();

extern int16_t Add_Propagator (Observable *observable, Propagator *propagator);
extern uint8_t Has_Propagators (Observable *observable);
extern bool Has_Propagator (Observable *source, char *source_key, Observable *destination, char *destination_key);
//extern Propagator* Get_Propagator (Observable *observable, char *key);
extern void Propagate (Observable *observable);
extern Propagator* Remove_Propagator (Observable *observable, Propagator *propagator);

/*
//void Observe (Observable o1, char *key1, Observable o2, char *key2);
void Forward (Observable o1, char *key1, Observable o2, char *key2); // (a.k.a., propagate) ...updates o2.key2 to value of o1.key1 whenever o1.key1 is updated...
void Filter(...);
void Notify_Of_Change (o1, o2); // Sends list/stream of changes to observer
*/

// Store a list of propagators in "observables"

// Each Device exposes it to Clay by creating an observable list.
// TODO: Rename to Observable_Provider
typedef struct Observable_Set {
	char *device_uuid;
	char *provider_uuid;
	Observable *first_observable;

	struct Observable_Set *previous;
	struct Observable_Set *next;
} Observable_Set;

extern Observable_Set* Create_Observable_Set (char *provider_uuid);
extern void Delete_Observable_Set (Observable_Set *observable_set);
extern int16_t Add_Observable (Observable_Set *observable_set, Observable *observable); // TODO: int16_t Add_Behavior (Behavior *loop, Behavior *behavior);
extern uint8_t Has_Observables (Observable_Set *observable_set);
extern Observable* Get_Observable (Observable_Set *observable_set, char *key);
extern Observable* Get_Observable_By_Index (Observable_Set *observable_set, int index);
extern Observable* Remove_Observable (Observable_Set *observable_set, Observable *observable); // TODO: Behavior* Remove_Behavior (Behavior *loop, Behavior *behavior);

// An "observable interface" contains a list of observables that will be
// exposed to Clay operating on a device. The observable interface provides
// the sole communication channel between some system. Systems that expose an
// observable interface are called "observable providers". Systems that are
// observable providers can be arbitrarily complex. They can be as simple as a
// GPIO pin on the host microcontroller or as complex as a distributed
// artificial intelligence running across multiple data centers on the
// Internet. This illustrates the intention that gave rise to the observable
// interface construct. That is, the intention to entirely separate Clay from
// the details of any system, physical or otherwise, that interacts with Clay.
// The dramatic range of complexity represented by these examples characterize
// one major advantage of Clay's architectural requirement that any system
// interacts with it do so by providing an observable interface to Clay.
//
// Notes:
// - Observable providers expose observables to observable interfaces. Each
//   device on which Clay operates has an observable interface, and they can
//   also expose their own observables to other devices operated by Clay, so
//   devices operated by Clay essentially exchange "chunks of interface"
//   by exposing observables to which they have been exposed (by the host
//   devices such as embedded microcontroller platforms) to other devices
//   operated by Clay. In other words, observables exposed by one provider
//   to another interface can be provided, in turn, to other interfaces.
typedef struct Observable_Interface {
	//char *uuid;
	Observable_Set *first_observable_provider;
} Observable_Interface;

extern Observable_Interface* Create_Observable_Interface ();
extern void Delete_Observable_Interface ();
extern int16_t Add_Observable_Provider (Observable_Interface *observable_interface, Observable_Set *observable_set); // TODO: int16_t Add_Behavior (Behavior *loop, Behavior *behavior);
extern uint8_t Has_Observable_Providers (Observable_Interface *observable_interface);
extern Observable_Set* Get_Observable_Provider (Observable_Interface *observable_interface, char *provider_uuid);
extern Observable_Set* Get_Observable_Provider_By_UUID (Observable_Interface *observable_interface, char *provider_uuid);
extern Observable_Set* Remove_Observable_Provider (Observable_Interface *observable_interface, Observable_Set *observable_set); // TODO: Behavior* Remove_Behavior (Behavior *loop, Behavior *behavior);

extern void Set_Observable_Provider_Device_UUID (Observable_Set *observable_provider, char *device_uuid);

// TODO: Message to return list of observable data sources available (for assignment/use in the programmer)

typedef struct Observable_Device {
	// k,v pair naming data variables

	/*
	// <HACK>
	uint32_t toggle_value; // TOGGLE CHANNEL (of observable), key-value with value equal to a channel
	// TODO: Add per-channel (per value) observing? (each would need its own observer list... with O(~1) way to access a channel's observer list)

	uint32_t waveform_sample_value; // TOGGLE CHANNEL (of observable)

	LDD_PPG_Tfloat pulse_period_seconds; // TOGGLE CHANNEL (of observable)
	uint16_t pulse_duty_cycle;
	// </HACK>
	*/

	MCU_GPIO_Profile mcu_hardware_profile;

	// Observers
	Observable_Set *observable_provider; // TODO: Replace toggle_value, waveform_sample_value, and pulse_* variables with an observable

} Observable_Device; // i.e., data stream
// e.g., Data_Stream adc_input_channel, digital_io_channel;
// note, this could be a constant value, an algorithm, or represent sensor data

//Add_Propagator (observable_device.sample, "toggle_value", channel.sample, "toggle_value");

// for channel profiles configured as input, set up periodic/interrupt driven updating of associated data source.
// for channel profiles configured as output, create pointer to data source from which to pull data when writing to the output channel (could be a constant source created just for the channel--e.g., "digital high")

extern Observable_Device platform_observable_profiles[CHANNEL_COUNT];

// When Observable_Profile calls notify of a Channel_Profile, Channel_Profile's handleNotify function looks at its configuration and copies values accordingly (from actual memory, not RAM).

typedef struct {
	uint8_t enabled;     // Specifies whether or not the channel being used.

	Channel_Number number; // TODO: Change to UUID? Don't attach to physical hardware?
	Channel_Direction direction;     // input or output
	Channel_Type type;    // (output) digital, pwm, (input) digital, analog, pwm

	Observable_Device *data;
	// Observable set stores the state information for the channel. This can be propagated from another set or stored directly.
	Observable_Set *observable_set; // TODO: Replace Observable_Device with Observable_Set (and update devices based on configuration set by channel)
	// Start_Observable, Stop_Observable, Set_Observable (calls propagate)

//	// <HACK>
//	Channel_Profile *output_data_source = NULL; // The source of output data
//	int8_t output_filter_index = -1;
//	// </HACK>

	// Monday:
	// 1. Remove Observable_Device
	// 2. Replace it with Observable_Set
	// 3. Rebuild to get that working...
	// 4. Get PWM demo working with new codebase...
	//
	// TODO: int16_t pulse_duty_cycle = (int16_t) Get_Observable_Data (&platform_observable_profiles[number], "pulse_duty_cycle");

	// TODO: Expected value. Set this to monitor the channel and look for a value. This will be used to set the LED state (maybe green or red, depending on correct or incorrect)
	// TODO: UUID for port. Used to record data and use it to submit data and request data.
	// TODO: UUID for transform.
} Channel_Profile;

////Globals   /////////////////////////////////////////////////////
extern Channel_Profile updated_channel_profile[CHANNEL_COUNT];
extern Channel_Profile channel_profile[CHANNEL_COUNT];

////Prototypes/////////////////////////////////////////////////////
extern bool Channel_Enable_All();
extern void Channel_Disable_All();

extern bool Channel_Enable(Channel_Number number);
extern void Channel_Disable(Channel_Number number);

extern bool Channel_Set_Type(Channel_Number number, Channel_Type type);
extern uint8_t Channel_Get_Type(Channel_Number number);

extern int32_t Channel_Set_Direction(Channel_Number number,
		Channel_Direction direction);
extern Channel_Direction Channel_Get_Direction(Channel_Number number);

extern int32_t Channel_Set_Data(Channel_Number number, int32_t data);
extern int32_t Channel_Get_Data(Channel_Number number);

extern void Channel_Periodic_Call();

int8_t Initialize_Channels();
int8_t Reset_Channels();
//int8_t Update_Channels ();

//int8_t Enable_Channels();
//int8_t Enable_Channel(uint8_t number, uint8_t enabled);
int8_t Apply_Channels();

#endif /* GPIO_H */
