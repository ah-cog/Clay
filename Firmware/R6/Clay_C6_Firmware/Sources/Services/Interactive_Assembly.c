#include "Interactive_Assembly.h"

// TODO: Implement callback timer and timeout reset (like in JavaScript).

int8_t button_mode = 0; // 0 = default, 1 = select channel
uint32_t button_mode_timeout = 0;
int8_t selected_channel = -1;
int8_t selected_channel_mode = -1;
int8_t changed_channel_mode = FALSE;

int8_t Enable_Interactive_Assembly () {
	Button_Register_Release_Response (&Request_Change_Selected_Channel);
	Button_Register_Hold_Response (DEFAULT_BUTTON_HOLD_TIME, &Request_Change_Selected_Channel_Mode);

   return TRUE;
}

void Request_Reset_Button () {
	int i;

	// Reset button logic state
	button_mode = 0;
	button_mode_timeout = 0;
	selected_channel--; // selected_channel = -1; // Michael likes the selected channel to be remembered. Allows picking up where left off.
	selected_channel_mode = 0;
	changed_channel_mode = FALSE;

	// Reset the state of all lights
	for (i = 0; i < 12; i++) {
		proposed_light_profiles[i].enabled = TRUE;
		Set_Light_Color (&proposed_light_profiles[i], 0, 0, 0);
	}

	// Apply the new light states
	Apply_Channels ();
	Apply_Channel_Lights ();
}

void Request_Change_Selected_Channel () {

	if (button_mode == 0) {
		button_mode = 1;
	}

	if (button_mode == 1) {

		button_mode_timeout = DEFAULT_BUTTON_MODE_TIMEOUT;

		if (changed_channel_mode == TRUE) {
			changed_channel_mode = FALSE;
			return;
		}

		if (selected_channel_mode == -1) {
			selected_channel_mode = 0;
		}
		Change_Selected_Channel ();
	}
}

void Change_Selected_Channel () {
	int i;
	selected_channel = (selected_channel + 1) % 12;

	if (selected_channel >= 0 && selected_channel < 12) {

		// Reset the state of all lights
		for (i = 0; i < 12; i++) {
			proposed_light_profiles[i].enabled = TRUE;
			Set_Light_Color (&proposed_light_profiles[i], 0, 0, 0);
		}

		// Set the state of the selected channel's light
		proposed_light_profiles[selected_channel].enabled = TRUE;

		if (selected_channel_mode == 0) {
			Set_Light_Color (&proposed_light_profiles[selected_channel], 50, 160, 200);
		} else if (selected_channel_mode == 1) {
			Set_Light_Color (&proposed_light_profiles[selected_channel], 250, 90, 20);
		}

		// TODO: Set the selected channel as input (if first device)

		// Apply the new light states
		Apply_Channels ();
		Apply_Channel_Lights ();
	}
}

void Request_Change_Selected_Channel_Mode () {
	if (changed_channel_mode == FALSE) {
		selected_channel_mode = (selected_channel_mode + 1) % 2;
		changed_channel_mode = TRUE;

		if (selected_channel_mode == 0) {
			Set_Light_Color (&proposed_light_profiles[selected_channel], 50, 160, 200);
		} else if (selected_channel_mode == 1) {
			Set_Light_Color (&proposed_light_profiles[selected_channel], 250, 90, 20);
		}

		// TODO: Set the selected channel as input (if first device)

		// Apply the new light states
		Apply_Channels ();
		Apply_Channel_Lights ();
	}
}
