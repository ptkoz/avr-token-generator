/*
 * Timeout.h
 *
 *  Created on: 22.02.2017
 *      Author: patryk
 *
 *  Message displayed on token request timeout.
 */

#ifndef SRC_VIEW_DISPLAY_MESSAGE_TIMEOUT_H_
#define SRC_VIEW_DISPLAY_MESSAGE_TIMEOUT_H_

#include "../Message.h"

namespace view { namespace display { namespace message {

class Timeout: public Message {
	public:
		Timeout();
		~Timeout();

		LiquidCrystal & printOn(LiquidCrystal & lcd);

	private:
		String line1 = "Brak odpowiedzi";
		String line2 = "Sprobuj ponownie";
};

}}}

#endif /* SRC_VIEW_DISPLAY_MESSAGE_TIMEOUT_H_ */
