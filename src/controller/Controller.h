/*
 * UI.h
 *
 *  Created on: 21.02.2017
 *      Author: patryk
 *
 *  This class is responsible for controlling user interfece
 *  of WiFi token generator. User interfece is composed by
 *  LCD screen, status LED and buzzer.
 */

#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

#include "../view/status/Led.h"
#include "../view/status/Buzzer.h"
#include "../view/Display.h"
#include "../model/State.h"

// type value represents state timeout in ms


class Controller {
	public:
		Controller();
		~Controller();

		void loop();
		void handleNewTokenRequest();
		void handleTokenReceive();
		void handleStateTimeout();
	private:
		view::status::led::Led led;
		view::status::buzzer::Buzzer buzzer;
		view::display::Display display;

		model::state::State state;
};

#endif
