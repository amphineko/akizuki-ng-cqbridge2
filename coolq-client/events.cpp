#include "stdafx.h"

uint8_t state_ = CLIENT_STATE_CND;

CLIENT_EVENT(const char *, event_get_client_info, AppInfo, 0)() {
	return CLIENT_APP_INFO;
}

CLIENT_EVENT(int32_t, event_set_client_disabled, SetClientDisabled, 0)() {
	assert(state_ == CLIENT_STATE_ENABLED);
	state_ = CLIENT_STATE_DISABLED;
	return 0;
}

CLIENT_EVENT(int32_t, event_set_client_enabled, SetClientEnabled, 0)() {
	assert(state_ == CLIENT_STATE_ENABLED);
	state_ = CLIENT_STATE_ENABLED;
	return 0;
}

CLIENT_EVENT(int32_t, event_set_host_exiting, SetHostExiting, 0)() {
	assert((state_ == CLIENT_STATE_DISABLED) || (state_ == CLIENT_STATE_ENABLED));
	if (state_ == CLIENT_STATE_ENABLED)
		event_set_client_disabled();
	// TODO: reject & finalize sockets
	return 0;
}

CLIENT_EVENT(int32_t, event_set_host_started, SetHostStarted, 0)() {
	assert(state_ == CLIENT_STATE_CND);
	state_ = CLIENT_STATE_DISABLED;
	// TODO: initialize & accept sockets
	return 0;
}

CLIENT_EVENT(int32_t, event_set_token, Initialize, 4)(int32_t token) {
	action_set_token(token);
	return 0;
}
