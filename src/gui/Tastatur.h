/* Copyright (c) 2012, Kose Alexander
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by Kose Alexander.
 * 4. Neither the name of Kose Alexander nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY KOSE ALEXANDER ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL KOSE ALEXANDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TASTATUR_H_
#define TASTATUR_H_

#include "ContainerElement.h"

namespace std {

class Button;

class Tastatur: public ContainerElement {
public:
	virtual ~Tastatur();
	void zeichneElement();
	void aendereGrossKlein();
	static Tastatur *gebeTastatur();
	static void drueckeAusrufeZeichen();
	static void druecke1();
	static void drueckeAt();
	static void druecke2();
	static void drueckeRaute();
	static void druecke3();
	static void drueckeDollar();
	static void druecke4();
	static void drueckeProzent();
	static void druecke5();
	static void drueckeDach();
	static void druecke6();
	static void drueckeUnd();
	static void druecke7();
	static void drueckeStern();
	static void druecke8();
	static void drueckeKlammerAuf();
	static void druecke9();
	static void drueckeKlammerZu();
	static void druecke0();
	static void drueckeRueckschritt();

	static void drueckeQ();
	static void drueckeq();
	static void drueckeW();
	static void drueckew();
	static void drueckeE();
	static void drueckee();
	static void drueckeR();
	static void druecker();
	static void drueckeT();
	static void druecket();
	static void drueckeY();
	static void drueckey();
	static void drueckeU();
	static void drueckeu();
	static void drueckeI();
	static void drueckei();
	static void drueckeO();
	static void drueckeo();
	static void drueckeP();
	static void drueckep();
	static void drueckeUnterstrich();
	static void drueckeBindestrich();
	//static void drueckeUe();
	//static void drueckeue();

	static void drueckeA();
	static void drueckea();
	static void drueckeS();
	static void drueckes();
	static void drueckeD();
	static void druecked();
	static void drueckeF();
	static void drueckef();
	static void drueckeG();
	static void drueckeg();
	static void drueckeH();
	static void drueckeh();
	static void drueckeJ();
	static void drueckej();
	static void drueckeK();
	static void drueckek();
	static void drueckeL();
	static void drueckel();
	static void drueckeDoppelpunkt();
	static void drueckeSemikolon();
	static void drueckeAnfuehrungsstriche();
	static void drueckeHochkomma();
	//static void drueckeOe();
	//static void drueckeoe();

	static void drueckeZ();
	static void drueckez();
	static void drueckeX();
	static void drueckex();
	static void drueckeC();
	static void drueckec();
	static void drueckeV();
	static void drueckev();
	static void drueckeB();
	static void drueckeb();
	static void drueckeN();
	static void druecken();
	static void drueckeM();
	static void drueckem();
	static void drueckeKleinerAls();
	static void drueckeKomma();
	static void drueckeGroesserAls();
	static void drueckePunkt();
	static void drueckeFragezeichen();
	static void drueckeSlash();
	//static void drueckeAe();
	//static void drueckeae();
	//static void drueckesz();

	static void drueckeGrossKlein();
	static void drueckeLeertaste();
private:
	static bool initialisiert;
	static Tastatur* tastatur;

	Tastatur();bool kleinSchreiben;

	Button *buttonAusrufeZeichen;
	Button *button1;
	Button *buttonAt;
	Button *button2;
	Button *buttonRaute;
	Button *button3;
	Button *buttonDollar;
	Button *button4;
	Button *buttonProzent;
	Button *button5;
	Button *buttonDach;
	Button *button6;
	Button *buttonUnd;
	Button *button7;
	Button *buttonStern;
	Button *button8;
	Button *buttonKlammerAuf;
	Button *button9;
	Button *buttonKlammerZu;
	Button *button0;
	Button *buttonRueckschritt;

	Button *buttonQ;
	Button *buttonq;
	Button *buttonW;
	Button *buttonw;
	Button *buttonE;
	Button *buttone;
	Button *buttonR;
	Button *buttonr;
	Button *buttonT;
	Button *buttont;
	Button *buttonY;
	Button *buttony;
	Button *buttonU;
	Button *buttonu;
	Button *buttonI;
	Button *buttoni;
	Button *buttonO;
	Button *buttono;
	Button *buttonP;
	Button *buttonp;
	Button *buttonUnterstrich;
	Button *buttonBindestrich;
	Button *buttonUe;
	Button *buttonue;

	Button *buttonA;
	Button *buttona;
	Button *buttonS;
	Button *buttons;
	Button *buttonD;
	Button *buttond;
	Button *buttonF;
	Button *buttonf;
	Button *buttonG;
	Button *buttong;
	Button *buttonH;
	Button *buttonh;
	Button *buttonJ;
	Button *buttonj;
	Button *buttonK;
	Button *buttonk;
	Button *buttonL;
	Button *buttonl;
	Button *buttonDoppelpunkt;
	Button *buttonSemikolon;
	Button *buttonAnfuehrungsstriche;
	Button *buttonHochkomma;
	Button *buttonOe;
	Button *buttonoe;

	Button *buttonZ;
	Button *buttonz;
	Button *buttonX;
	Button *buttonx;
	Button *buttonC;
	Button *buttonc;
	Button *buttonV;
	Button *buttonv;
	Button *buttonB;
	Button *buttonb;
	Button *buttonN;
	Button *buttonn;
	Button *buttonM;
	Button *buttonm;
	Button *buttonKleinerAls;
	Button *buttonKomma;
	Button *buttonGroesserAls;
	Button *buttonPunkt;
	Button *buttonFragezeichen;
	Button *buttonSlash;
	Button *buttonAe;
	Button *buttonae;
	//Button *buttonsz;

	Button *buttonGrossKlein;
	Button *buttonLeertaste;
};

}
#endif /* TASTATUR_H_ */
