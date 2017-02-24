/*
 * Busy.h
 *
 *  Created on: 22.02.2017
 *      Author: patryk
 *
 *  Message displayed when token is generating.
 */

#ifndef SRC_VIEW_DISPLAY_MESSAGE_TOKEN_H_
#define SRC_VIEW_DISPLAY_MESSAGE_TOKEN_H_

#include "../Message.h"

namespace view { namespace display { namespace message {

class Token: public Message {
	public:
		Token(const String & token);
		~Token();

		LiquidCrystal & printOn(LiquidCrystal & lcd);
	private:
		String msg = "Twoj token WiFi:";
		String token;
};

}}}

#endif /* SRC_VIEW_DISPLAY_MESSAGE_TOKEN_H_ */
