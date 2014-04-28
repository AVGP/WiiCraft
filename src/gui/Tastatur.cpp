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

#include "Tastatur.h"

#include <string>
#include "GrafikHandler.h"
#include "Button.h"

using namespace std;

bool Tastatur::initialisiert = false;
Tastatur *Tastatur::tastatur;

Tastatur::~Tastatur() {
}

Tastatur *Tastatur::gebeTastatur() {
	if (!Tastatur::initialisiert) {
		Tastatur::tastatur = new Tastatur();
		Tastatur::initialisiert = true;
	}
	return Tastatur::tastatur;
}

Tastatur::Tastatur() {
	ContainerElement::setzeStandardWerte();

	this->setzeX(0);
	this->setzeY(300);
	this->setzeHoehe(180);
	this->setzeBreite(640);

	char buchstabe;
	string *buchstabeS;

	// Button erstellen
	this->buttonAusrufeZeichen = new Button(20, 300, "!");
	this->button1 = new Button(20, 300, "1");
	this->buttonAt = new Button(70, 300, "@");
	this->button2 = new Button(70, 300, "2");
	this->buttonRaute = new Button(120, 300, "#");
	this->button3 = new Button(120, 300, "3");
	this->buttonDollar = new Button(170, 300, "$");
	this->button4 = new Button(170, 300, "4");
	this->buttonProzent = new Button(220, 300, "%");
	this->button5 = new Button(220, 300, "5");
	this->buttonDach = new Button(270, 300, "^");
	this->button6 = new Button(270, 300, "6");
	this->buttonUnd = new Button(320, 300, "&");
	this->button7 = new Button(320, 300, "7");
	this->buttonStern = new Button(370, 300, "*");
	this->button8 = new Button(370, 300, "8");
	this->buttonKlammerAuf = new Button(420, 300, "(");
	this->button9 = new Button(420, 300, "9");
	this->buttonKlammerZu = new Button(470, 300, ")");
	this->button0 = new Button(470, 300, "0");
	this->buttonRueckschritt = new Button(520, 300, "<---");

	this->buttonQ = new Button(20, 330, "Q");
	this->buttonq = new Button(20, 330, "q");
	this->buttonW = new Button(70, 330, "W");
	this->buttonw = new Button(70, 330, "w");
	this->buttonE = new Button(120, 330, "E");
	this->buttone = new Button(120, 330, "e");
	this->buttonR = new Button(170, 330, "R");
	this->buttonr = new Button(170, 330, "r");
	this->buttonT = new Button(220, 330, "T");
	this->buttont = new Button(220, 330, "t");
	this->buttonY = new Button(270, 330, "Y");
	this->buttony = new Button(270, 330, "y");
	this->buttonU = new Button(320, 330, "U");
	this->buttonu = new Button(320, 330, "u");
	this->buttonI = new Button(370, 330, "I");
	this->buttoni = new Button(370, 330, "i");
	this->buttonO = new Button(420, 330, "O");
	this->buttono = new Button(420, 330, "o");
	this->buttonP = new Button(470, 330, "P");
	this->buttonp = new Button(470, 330, "p");
	this->buttonUnterstrich = new Button(520, 330, "_");
	this->buttonBindestrich = new Button(520, 330, "-");
	buchstabe = 0x9a;
	buchstabeS = new string(&buchstabe);
	this->buttonUe = new Button(570, 330, *buchstabeS);
	this->buttonUe->deaktivieren(true);
	buchstabe = 0x81;
	buchstabeS = new string(&buchstabe);
	this->buttonue = new Button(570, 330, *buchstabeS);
	this->buttonue->deaktivieren(true);

	this->buttonA = new Button(20, 360, "A");
	this->buttona = new Button(20, 360, "a");
	this->buttonS = new Button(70, 360, "S");
	this->buttons = new Button(70, 360, "s");
	this->buttonD = new Button(120, 360, "D");
	this->buttond = new Button(120, 360, "d");
	this->buttonF = new Button(170, 360, "F");
	this->buttonf = new Button(170, 360, "f");
	this->buttonG = new Button(220, 360, "G");
	this->buttong = new Button(220, 360, "g");
	this->buttonH = new Button(270, 360, "H");
	this->buttonh = new Button(270, 360, "h");
	this->buttonJ = new Button(320, 360, "J");
	this->buttonj = new Button(320, 360, "j");
	this->buttonK = new Button(370, 360, "K");
	this->buttonk = new Button(370, 360, "k");
	this->buttonL = new Button(420, 360, "L");
	this->buttonl = new Button(420, 360, "l");
	this->buttonDoppelpunkt = new Button(470, 360, ":");
	this->buttonSemikolon = new Button(470, 360, ";");
	this->buttonAnfuehrungsstriche = new Button(520, 360, "\"");
	this->buttonHochkomma = new Button(520, 360, "'");
	buchstabe = 0x99;
	buchstabeS = new string(&buchstabe);
	this->buttonOe = new Button(570, 360, *buchstabeS);
	this->buttonOe->deaktivieren(true);
	buchstabe = 0x94;
	buchstabeS = new string(&buchstabe);
	this->buttonoe = new Button(570, 360, *buchstabeS);
	this->buttonoe->deaktivieren(true);

	this->buttonZ = new Button(20, 390, "Z");
	this->buttonz = new Button(20, 390, "z");
	this->buttonX = new Button(70, 390, "X");
	this->buttonx = new Button(70, 390, "x");
	this->buttonC = new Button(120, 390, "C");
	this->buttonc = new Button(120, 390, "c");
	this->buttonV = new Button(170, 390, "V");
	this->buttonv = new Button(170, 390, "v");
	this->buttonB = new Button(220, 390, "B");
	this->buttonb = new Button(220, 390, "b");
	this->buttonN = new Button(270, 390, "N");
	this->buttonn = new Button(270, 390, "n");
	this->buttonM = new Button(320, 390, "M");
	this->buttonm = new Button(320, 390, "m");
	this->buttonKleinerAls = new Button(370, 390, "<");
	this->buttonKomma = new Button(370, 390, ",");
	this->buttonGroesserAls = new Button(420, 390, ">");
	this->buttonPunkt = new Button(420, 390, ".");
	this->buttonFragezeichen = new Button(470, 390, "?");
	this->buttonSlash = new Button(470, 390, "/");
	buchstabe = 0x8e;
	buchstabeS = new string(&buchstabe);
	this->buttonAe = new Button(520, 390, *buchstabeS);
	this->buttonAe->deaktivieren(true);
	buchstabe = 0x84;
	buchstabeS = new string(&buchstabe);
	this->buttonae = new Button(520, 390, *buchstabeS);
	this->buttonae->deaktivieren(true);
	//this->buttonsz = new Button(570, 390, "ß");

	this->buttonGrossKlein = new Button(20, 420, "ABC/abc");
	this->buttonLeertaste = new Button(200, 420, "                      ");

	// kleine Buchstaben zuerst darstellen
	this->kleinSchreiben = false;
	this->aendereGrossKlein();

	// Event hinzufuegen
	this->buttonAusrufeZeichen->setzeBeimKlicken(
			&Tastatur::drueckeAusrufeZeichen);
	this->button1->setzeBeimKlicken(&Tastatur::druecke1);
	this->buttonAt->setzeBeimKlicken(&Tastatur::drueckeAt);
	this->button2->setzeBeimKlicken(&Tastatur::druecke2);
	this->buttonRaute->setzeBeimKlicken(&Tastatur::drueckeRaute);
	this->button3->setzeBeimKlicken(&Tastatur::druecke3);
	this->buttonDollar->setzeBeimKlicken(&Tastatur::drueckeDollar);
	this->button4->setzeBeimKlicken(&Tastatur::druecke4);
	this->buttonProzent->setzeBeimKlicken(&Tastatur::drueckeProzent);
	this->button5->setzeBeimKlicken(&Tastatur::druecke5);
	this->buttonDach->setzeBeimKlicken(&Tastatur::drueckeDach);
	this->button6->setzeBeimKlicken(&Tastatur::druecke6);
	this->buttonUnd->setzeBeimKlicken(&Tastatur::drueckeUnd);
	this->button7->setzeBeimKlicken(&Tastatur::druecke7);
	this->buttonStern->setzeBeimKlicken(&Tastatur::drueckeStern);
	this->button8->setzeBeimKlicken(&Tastatur::druecke8);
	this->buttonKlammerAuf->setzeBeimKlicken(&Tastatur::drueckeKlammerAuf);
	this->button9->setzeBeimKlicken(&Tastatur::druecke9);
	this->buttonKlammerZu->setzeBeimKlicken(&Tastatur::drueckeKlammerZu);
	this->button0->setzeBeimKlicken(&Tastatur::druecke0);
	this->buttonRueckschritt->setzeBeimKlicken(&Tastatur::drueckeRueckschritt);

	this->buttonQ->setzeBeimKlicken(&Tastatur::drueckeQ);
	this->buttonq->setzeBeimKlicken(&Tastatur::drueckeq);
	this->buttonW->setzeBeimKlicken(&Tastatur::drueckeW);
	this->buttonw->setzeBeimKlicken(&Tastatur::drueckew);
	this->buttonE->setzeBeimKlicken(&Tastatur::drueckeE);
	this->buttone->setzeBeimKlicken(&Tastatur::drueckee);
	this->buttonR->setzeBeimKlicken(&Tastatur::drueckeR);
	this->buttonr->setzeBeimKlicken(&Tastatur::druecker);
	this->buttonT->setzeBeimKlicken(&Tastatur::drueckeT);
	this->buttont->setzeBeimKlicken(&Tastatur::druecket);
	this->buttonY->setzeBeimKlicken(&Tastatur::drueckeY);
	this->buttony->setzeBeimKlicken(&Tastatur::drueckey);
	this->buttonU->setzeBeimKlicken(&Tastatur::drueckeU);
	this->buttonu->setzeBeimKlicken(&Tastatur::drueckeu);
	this->buttonI->setzeBeimKlicken(&Tastatur::drueckeI);
	this->buttoni->setzeBeimKlicken(&Tastatur::drueckei);
	this->buttonO->setzeBeimKlicken(&Tastatur::drueckeO);
	this->buttono->setzeBeimKlicken(&Tastatur::drueckeo);
	this->buttonP->setzeBeimKlicken(&Tastatur::drueckeP);
	this->buttonp->setzeBeimKlicken(&Tastatur::drueckep);
	this->buttonUnterstrich->setzeBeimKlicken(&Tastatur::drueckeUnterstrich);
	this->buttonBindestrich->setzeBeimKlicken(&Tastatur::drueckeBindestrich);
	//this->buttonUe->setzeBeimKlicken(&Tastatur::drueckeUe);
	//this->buttonue->setzeBeimKlicken(&Tastatur::drueckeue);

	this->buttonA->setzeBeimKlicken(&Tastatur::drueckeA);
	this->buttona->setzeBeimKlicken(&Tastatur::drueckea);
	this->buttonS->setzeBeimKlicken(&Tastatur::drueckeS);
	this->buttons->setzeBeimKlicken(&Tastatur::drueckes);
	this->buttonD->setzeBeimKlicken(&Tastatur::drueckeD);
	this->buttond->setzeBeimKlicken(&Tastatur::druecked);
	this->buttonF->setzeBeimKlicken(&Tastatur::drueckeF);
	this->buttonf->setzeBeimKlicken(&Tastatur::drueckef);
	this->buttonG->setzeBeimKlicken(&Tastatur::drueckeG);
	this->buttong->setzeBeimKlicken(&Tastatur::drueckeg);
	this->buttonH->setzeBeimKlicken(&Tastatur::drueckeH);
	this->buttonh->setzeBeimKlicken(&Tastatur::drueckeh);
	this->buttonJ->setzeBeimKlicken(&Tastatur::drueckeJ);
	this->buttonj->setzeBeimKlicken(&Tastatur::drueckej);
	this->buttonK->setzeBeimKlicken(&Tastatur::drueckeK);
	this->buttonk->setzeBeimKlicken(&Tastatur::drueckek);
	this->buttonL->setzeBeimKlicken(&Tastatur::drueckeL);
	this->buttonl->setzeBeimKlicken(&Tastatur::drueckel);
	this->buttonDoppelpunkt->setzeBeimKlicken(&Tastatur::drueckeDoppelpunkt);
	this->buttonSemikolon->setzeBeimKlicken(&Tastatur::drueckeSemikolon);
	this->buttonAnfuehrungsstriche->setzeBeimKlicken(
			&Tastatur::drueckeAnfuehrungsstriche);
	this->buttonHochkomma->setzeBeimKlicken(&Tastatur::drueckeHochkomma);
	//this->buttonOe->setzeBeimKlicken(&Tastatur::drueckeOe);
	//this->buttonoe->setzeBeimKlicken(&Tastatur::drueckeoe);

	this->buttonZ->setzeBeimKlicken(&Tastatur::drueckeZ);
	this->buttonz->setzeBeimKlicken(&Tastatur::drueckez);
	this->buttonX->setzeBeimKlicken(&Tastatur::drueckeX);
	this->buttonx->setzeBeimKlicken(&Tastatur::drueckex);
	this->buttonC->setzeBeimKlicken(&Tastatur::drueckeC);
	this->buttonc->setzeBeimKlicken(&Tastatur::drueckec);
	this->buttonV->setzeBeimKlicken(&Tastatur::drueckeV);
	this->buttonv->setzeBeimKlicken(&Tastatur::drueckev);
	this->buttonB->setzeBeimKlicken(&Tastatur::drueckeB);
	this->buttonb->setzeBeimKlicken(&Tastatur::drueckeb);
	this->buttonN->setzeBeimKlicken(&Tastatur::drueckeN);
	this->buttonn->setzeBeimKlicken(&Tastatur::druecken);
	this->buttonM->setzeBeimKlicken(&Tastatur::drueckeM);
	this->buttonm->setzeBeimKlicken(&Tastatur::drueckem);
	this->buttonKleinerAls->setzeBeimKlicken(&Tastatur::drueckeKleinerAls);
	this->buttonKomma->setzeBeimKlicken(&Tastatur::drueckeKomma);
	this->buttonGroesserAls->setzeBeimKlicken(&Tastatur::drueckeGroesserAls);
	this->buttonPunkt->setzeBeimKlicken(&Tastatur::drueckePunkt);
	this->buttonFragezeichen->setzeBeimKlicken(&Tastatur::drueckeFragezeichen);
	this->buttonSlash->setzeBeimKlicken(&Tastatur::drueckeSlash);
	//this->buttonAe->setzeBeimKlicken(&Tastatur::drueckeAe);
	//this->buttonae->setzeBeimKlicken(&Tastatur::drueckeae);
	//this->buttonsz->setzeBeimKlicken(&Tastatur::drueckesz);

	this->buttonGrossKlein->setzeBeimKlicken(&Tastatur::drueckeGrossKlein);
	this->buttonLeertaste->setzeBeimKlicken(&Tastatur::drueckeLeertaste);

	// Button hinzufuegen
	this->fuegeUnterElementHinzu(this->buttonAusrufeZeichen);
	this->fuegeUnterElementHinzu(this->button1);
	this->fuegeUnterElementHinzu(this->buttonAt);
	this->fuegeUnterElementHinzu(this->button2);
	this->fuegeUnterElementHinzu(this->buttonRaute);
	this->fuegeUnterElementHinzu(this->button3);
	this->fuegeUnterElementHinzu(this->buttonDollar);
	this->fuegeUnterElementHinzu(this->button4);
	this->fuegeUnterElementHinzu(this->buttonProzent);
	this->fuegeUnterElementHinzu(this->button5);
	this->fuegeUnterElementHinzu(this->buttonDach);
	this->fuegeUnterElementHinzu(this->button6);
	this->fuegeUnterElementHinzu(this->buttonUnd);
	this->fuegeUnterElementHinzu(this->button7);
	this->fuegeUnterElementHinzu(this->buttonStern);
	this->fuegeUnterElementHinzu(this->button8);
	this->fuegeUnterElementHinzu(this->buttonKlammerAuf);
	this->fuegeUnterElementHinzu(this->button9);
	this->fuegeUnterElementHinzu(this->buttonKlammerZu);
	this->fuegeUnterElementHinzu(this->button0);
	this->fuegeUnterElementHinzu(this->buttonRueckschritt);

	this->fuegeUnterElementHinzu(this->buttonQ);
	this->fuegeUnterElementHinzu(this->buttonq);
	this->fuegeUnterElementHinzu(this->buttonW);
	this->fuegeUnterElementHinzu(this->buttonw);
	this->fuegeUnterElementHinzu(this->buttonE);
	this->fuegeUnterElementHinzu(this->buttone);
	this->fuegeUnterElementHinzu(this->buttonR);
	this->fuegeUnterElementHinzu(this->buttonr);
	this->fuegeUnterElementHinzu(this->buttonT);
	this->fuegeUnterElementHinzu(this->buttont);
	this->fuegeUnterElementHinzu(this->buttonY);
	this->fuegeUnterElementHinzu(this->buttony);
	this->fuegeUnterElementHinzu(this->buttonU);
	this->fuegeUnterElementHinzu(this->buttonu);
	this->fuegeUnterElementHinzu(this->buttonI);
	this->fuegeUnterElementHinzu(this->buttoni);
	this->fuegeUnterElementHinzu(this->buttonO);
	this->fuegeUnterElementHinzu(this->buttono);
	this->fuegeUnterElementHinzu(this->buttonP);
	this->fuegeUnterElementHinzu(this->buttonp);
	this->fuegeUnterElementHinzu(this->buttonUnterstrich);
	this->fuegeUnterElementHinzu(this->buttonBindestrich);
	this->fuegeUnterElementHinzu(this->buttonUe);
	this->fuegeUnterElementHinzu(this->buttonue);

	this->fuegeUnterElementHinzu(this->buttonA);
	this->fuegeUnterElementHinzu(this->buttona);
	this->fuegeUnterElementHinzu(this->buttonS);
	this->fuegeUnterElementHinzu(this->buttons);
	this->fuegeUnterElementHinzu(this->buttonD);
	this->fuegeUnterElementHinzu(this->buttond);
	this->fuegeUnterElementHinzu(this->buttonF);
	this->fuegeUnterElementHinzu(this->buttonf);
	this->fuegeUnterElementHinzu(this->buttonG);
	this->fuegeUnterElementHinzu(this->buttong);
	this->fuegeUnterElementHinzu(this->buttonH);
	this->fuegeUnterElementHinzu(this->buttonh);
	this->fuegeUnterElementHinzu(this->buttonJ);
	this->fuegeUnterElementHinzu(this->buttonj);
	this->fuegeUnterElementHinzu(this->buttonK);
	this->fuegeUnterElementHinzu(this->buttonk);
	this->fuegeUnterElementHinzu(this->buttonL);
	this->fuegeUnterElementHinzu(this->buttonl);
	this->fuegeUnterElementHinzu(this->buttonDoppelpunkt);
	this->fuegeUnterElementHinzu(this->buttonSemikolon);
	this->fuegeUnterElementHinzu(this->buttonAnfuehrungsstriche);
	this->fuegeUnterElementHinzu(this->buttonHochkomma);
	this->fuegeUnterElementHinzu(this->buttonOe);
	this->fuegeUnterElementHinzu(this->buttonoe);

	this->fuegeUnterElementHinzu(this->buttonZ);
	this->fuegeUnterElementHinzu(this->buttonz);
	this->fuegeUnterElementHinzu(this->buttonX);
	this->fuegeUnterElementHinzu(this->buttonx);
	this->fuegeUnterElementHinzu(this->buttonC);
	this->fuegeUnterElementHinzu(this->buttonc);
	this->fuegeUnterElementHinzu(this->buttonV);
	this->fuegeUnterElementHinzu(this->buttonv);
	this->fuegeUnterElementHinzu(this->buttonB);
	this->fuegeUnterElementHinzu(this->buttonb);
	this->fuegeUnterElementHinzu(this->buttonN);
	this->fuegeUnterElementHinzu(this->buttonn);
	this->fuegeUnterElementHinzu(this->buttonM);
	this->fuegeUnterElementHinzu(this->buttonm);
	this->fuegeUnterElementHinzu(this->buttonKleinerAls);
	this->fuegeUnterElementHinzu(this->buttonKomma);
	this->fuegeUnterElementHinzu(this->buttonGroesserAls);
	this->fuegeUnterElementHinzu(this->buttonPunkt);
	this->fuegeUnterElementHinzu(this->buttonFragezeichen);
	this->fuegeUnterElementHinzu(this->buttonSlash);
	this->fuegeUnterElementHinzu(this->buttonAe);
	this->fuegeUnterElementHinzu(this->buttonae);
	//this->fuegeUnterElementHinzu(this->buttonsz);

	this->fuegeUnterElementHinzu(this->buttonGrossKlein);
	this->fuegeUnterElementHinzu(this->buttonLeertaste);
}

void Tastatur::zeichneElement() {
	if (this->istSichtbar()) {
		this->zeichneUnterElement();
	}
}

void Tastatur::aendereGrossKlein() {
	this->kleinSchreiben = !this->kleinSchreiben;

	if (this->kleinSchreiben) {
		this->buttonAusrufeZeichen->sichtbarkeit(false);
		this->button1->sichtbarkeit(true);
		this->buttonAt->sichtbarkeit(false);
		this->button2->sichtbarkeit(true);
		this->buttonRaute->sichtbarkeit(false);
		this->button3->sichtbarkeit(true);
		this->buttonDollar->sichtbarkeit(false);
		this->button4->sichtbarkeit(true);
		this->buttonProzent->sichtbarkeit(false);
		this->button5->sichtbarkeit(true);
		this->buttonDach->sichtbarkeit(false);
		this->button6->sichtbarkeit(true);
		this->buttonUnd->sichtbarkeit(false);
		this->button7->sichtbarkeit(true);
		this->buttonStern->sichtbarkeit(false);
		this->button8->sichtbarkeit(true);
		this->buttonKlammerAuf->sichtbarkeit(false);
		this->button9->sichtbarkeit(true);
		this->buttonKlammerZu->sichtbarkeit(false);
		this->button0->sichtbarkeit(true);

		this->buttonQ->sichtbarkeit(false);
		this->buttonq->sichtbarkeit(true);
		this->buttonW->sichtbarkeit(false);
		this->buttonw->sichtbarkeit(true);
		this->buttonE->sichtbarkeit(false);
		this->buttone->sichtbarkeit(true);
		this->buttonR->sichtbarkeit(false);
		this->buttonr->sichtbarkeit(true);
		this->buttonT->sichtbarkeit(false);
		this->buttont->sichtbarkeit(true);
		this->buttonY->sichtbarkeit(false);
		this->buttony->sichtbarkeit(true);
		this->buttonU->sichtbarkeit(false);
		this->buttonu->sichtbarkeit(true);
		this->buttonI->sichtbarkeit(false);
		this->buttoni->sichtbarkeit(true);
		this->buttonO->sichtbarkeit(false);
		this->buttono->sichtbarkeit(true);
		this->buttonP->sichtbarkeit(false);
		this->buttonp->sichtbarkeit(true);
		this->buttonUnterstrich->sichtbarkeit(false);
		this->buttonBindestrich->sichtbarkeit(true);
		this->buttonUe->sichtbarkeit(false);
		this->buttonue->sichtbarkeit(true);

		this->buttonA->sichtbarkeit(false);
		this->buttona->sichtbarkeit(true);
		this->buttonS->sichtbarkeit(false);
		this->buttons->sichtbarkeit(true);
		this->buttonD->sichtbarkeit(false);
		this->buttond->sichtbarkeit(true);
		this->buttonF->sichtbarkeit(false);
		this->buttonf->sichtbarkeit(true);
		this->buttonG->sichtbarkeit(false);
		this->buttong->sichtbarkeit(true);
		this->buttonH->sichtbarkeit(false);
		this->buttonh->sichtbarkeit(true);
		this->buttonJ->sichtbarkeit(false);
		this->buttonj->sichtbarkeit(true);
		this->buttonK->sichtbarkeit(false);
		this->buttonk->sichtbarkeit(true);
		this->buttonL->sichtbarkeit(false);
		this->buttonl->sichtbarkeit(true);
		this->buttonDoppelpunkt->sichtbarkeit(false);
		this->buttonSemikolon->sichtbarkeit(true);
		this->buttonAnfuehrungsstriche->sichtbarkeit(false);
		this->buttonHochkomma->sichtbarkeit(true);
		this->buttonOe->sichtbarkeit(false);
		this->buttonoe->sichtbarkeit(true);

		this->buttonZ->sichtbarkeit(false);
		this->buttonz->sichtbarkeit(true);
		this->buttonX->sichtbarkeit(false);
		this->buttonx->sichtbarkeit(true);
		this->buttonC->sichtbarkeit(false);
		this->buttonc->sichtbarkeit(true);
		this->buttonV->sichtbarkeit(false);
		this->buttonv->sichtbarkeit(true);
		this->buttonB->sichtbarkeit(false);
		this->buttonb->sichtbarkeit(true);
		this->buttonN->sichtbarkeit(false);
		this->buttonn->sichtbarkeit(true);
		this->buttonM->sichtbarkeit(false);
		this->buttonm->sichtbarkeit(true);
		this->buttonKleinerAls->sichtbarkeit(false);
		this->buttonKomma->sichtbarkeit(true);
		this->buttonGroesserAls->sichtbarkeit(false);
		this->buttonPunkt->sichtbarkeit(true);
		this->buttonFragezeichen->sichtbarkeit(false);
		this->buttonSlash->sichtbarkeit(true);
		this->buttonAe->sichtbarkeit(false);
		this->buttonae->sichtbarkeit(true);
	} else {
		this->buttonAusrufeZeichen->sichtbarkeit(true);
		this->button1->sichtbarkeit(false);
		this->buttonAt->sichtbarkeit(true);
		this->button2->sichtbarkeit(false);
		this->buttonRaute->sichtbarkeit(true);
		this->button3->sichtbarkeit(false);
		this->buttonDollar->sichtbarkeit(true);
		this->button4->sichtbarkeit(false);
		this->buttonProzent->sichtbarkeit(true);
		this->button5->sichtbarkeit(false);
		this->buttonDach->sichtbarkeit(true);
		this->button6->sichtbarkeit(false);
		this->buttonUnd->sichtbarkeit(true);
		this->button7->sichtbarkeit(false);
		this->buttonStern->sichtbarkeit(true);
		this->button8->sichtbarkeit(false);
		this->buttonKlammerAuf->sichtbarkeit(true);
		this->button9->sichtbarkeit(false);
		this->buttonKlammerZu->sichtbarkeit(true);
		this->button0->sichtbarkeit(false);

		this->buttonQ->sichtbarkeit(true);
		this->buttonq->sichtbarkeit(false);
		this->buttonW->sichtbarkeit(true);
		this->buttonw->sichtbarkeit(false);
		this->buttonE->sichtbarkeit(true);
		this->buttone->sichtbarkeit(false);
		this->buttonR->sichtbarkeit(true);
		this->buttonr->sichtbarkeit(false);
		this->buttonT->sichtbarkeit(true);
		this->buttont->sichtbarkeit(false);
		this->buttonY->sichtbarkeit(true);
		this->buttony->sichtbarkeit(false);
		this->buttonU->sichtbarkeit(true);
		this->buttonu->sichtbarkeit(false);
		this->buttonI->sichtbarkeit(true);
		this->buttoni->sichtbarkeit(false);
		this->buttonO->sichtbarkeit(true);
		this->buttono->sichtbarkeit(false);
		this->buttonP->sichtbarkeit(true);
		this->buttonp->sichtbarkeit(false);
		this->buttonUnterstrich->sichtbarkeit(true);
		this->buttonBindestrich->sichtbarkeit(false);
		this->buttonUe->sichtbarkeit(true);
		this->buttonue->sichtbarkeit(false);

		this->buttonA->sichtbarkeit(true);
		this->buttona->sichtbarkeit(false);
		this->buttonS->sichtbarkeit(true);
		this->buttons->sichtbarkeit(false);
		this->buttonD->sichtbarkeit(true);
		this->buttond->sichtbarkeit(false);
		this->buttonF->sichtbarkeit(true);
		this->buttonf->sichtbarkeit(false);
		this->buttonG->sichtbarkeit(true);
		this->buttong->sichtbarkeit(false);
		this->buttonH->sichtbarkeit(true);
		this->buttonh->sichtbarkeit(false);
		this->buttonJ->sichtbarkeit(true);
		this->buttonj->sichtbarkeit(false);
		this->buttonK->sichtbarkeit(true);
		this->buttonk->sichtbarkeit(false);
		this->buttonL->sichtbarkeit(true);
		this->buttonl->sichtbarkeit(false);
		this->buttonDoppelpunkt->sichtbarkeit(true);
		this->buttonSemikolon->sichtbarkeit(false);
		this->buttonAnfuehrungsstriche->sichtbarkeit(true);
		this->buttonHochkomma->sichtbarkeit(false);
		this->buttonOe->sichtbarkeit(true);
		this->buttonoe->sichtbarkeit(false);

		this->buttonZ->sichtbarkeit(true);
		this->buttonz->sichtbarkeit(false);
		this->buttonX->sichtbarkeit(true);
		this->buttonx->sichtbarkeit(false);
		this->buttonC->sichtbarkeit(true);
		this->buttonc->sichtbarkeit(false);
		this->buttonV->sichtbarkeit(true);
		this->buttonv->sichtbarkeit(false);
		this->buttonB->sichtbarkeit(true);
		this->buttonb->sichtbarkeit(false);
		this->buttonN->sichtbarkeit(true);
		this->buttonn->sichtbarkeit(false);
		this->buttonM->sichtbarkeit(true);
		this->buttonm->sichtbarkeit(false);
		this->buttonKleinerAls->sichtbarkeit(true);
		this->buttonKomma->sichtbarkeit(false);
		this->buttonGroesserAls->sichtbarkeit(true);
		this->buttonPunkt->sichtbarkeit(false);
		this->buttonFragezeichen->sichtbarkeit(true);
		this->buttonSlash->sichtbarkeit(false);
		this->buttonAe->sichtbarkeit(true);
		this->buttonae->sichtbarkeit(false);
	}
}

void Tastatur::drueckeAusrufeZeichen() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("!");
		textElement->setzeText(text);
	}
}
void Tastatur::druecke1() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("1");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeAt() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("@");
		textElement->setzeText(text);
	}
}
void Tastatur::druecke2() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("2");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeRaute() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("#");
		textElement->setzeText(text);
	}
}
void Tastatur::druecke3() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("3");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeDollar() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("$");
		textElement->setzeText(text);
	}
}
void Tastatur::druecke4() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("4");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeProzent() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("%");
		textElement->setzeText(text);
	}
}
void Tastatur::druecke5() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("5");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeDach() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("^");
		textElement->setzeText(text);
	}
}
void Tastatur::druecke6() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("6");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeUnd() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("&");
		textElement->setzeText(text);
	}
}
void Tastatur::druecke7() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("7");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeStern() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("*");
		textElement->setzeText(text);
	}
}
void Tastatur::druecke8() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("8");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeKlammerAuf() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("(");
		textElement->setzeText(text);
	}
}
void Tastatur::druecke9() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("9");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeKlammerZu() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append(")");
		textElement->setzeText(text);
	}
}
void Tastatur::druecke0() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("0");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeRueckschritt() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		if (text.size() > 0) {
			text = text.substr(0, text.size() - 1);
			textElement->setzeText(text);
		}
	}
}

void Tastatur::drueckeQ() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("Q");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeq() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("q");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeW() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("W");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckew() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("w");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeE() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("E");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckee() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("e");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeR() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("R");
		textElement->setzeText(text);
	}
}
void Tastatur::druecker() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("r");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeT() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("T");
		textElement->setzeText(text);
	}
}
void Tastatur::druecket() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("t");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeY() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("Y");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckey() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("y");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeU() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("U");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeu() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("u");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeI() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("I");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckei() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("i");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeO() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("O");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeo() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("o");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeP() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("P");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckep() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("p");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeUnterstrich() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("_");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeBindestrich() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("-");
		textElement->setzeText(text);
	}
}
/*void Tastatur::drueckeUe() {
 TextElement *textElement =
 dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
 if (textElement != 0) {
 string text = textElement->gebeText();
 text.append("Ü");
 textElement->setzeText(text);
 }
 }
 void Tastatur::drueckeue() {
 TextElement *textElement =
 dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
 if (textElement != 0) {
 string text = textElement->gebeText();
 text.append("ü");
 textElement->setzeText(text);
 }
 }*/

void Tastatur::drueckeA() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("A");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckea() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("a");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeS() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("S");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckes() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("s");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeD() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("D");
		textElement->setzeText(text);
	}
}
void Tastatur::druecked() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("d");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeF() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("F");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckef() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("f");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeG() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("G");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeg() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("g");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeH() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("H");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeh() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("h");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeJ() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("J");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckej() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("j");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeK() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("K");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckek() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("k");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeL() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("L");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckel() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("l");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeDoppelpunkt() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append(":");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeSemikolon() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append(";");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeAnfuehrungsstriche() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("\"");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeHochkomma() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("'");
		textElement->setzeText(text);
	}
}
/*void Tastatur::drueckeOe() {
 TextElement *textElement =
 dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
 if (textElement != 0) {
 string text = textElement->gebeText();
 text.append("Ö");
 textElement->setzeText(text);
 }
 }
 void Tastatur::drueckeoe() {
 TextElement *textElement =
 dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
 if (textElement != 0) {
 string text = textElement->gebeText();
 text.append("ö");
 textElement->setzeText(text);
 }
 }*/

void Tastatur::drueckeZ() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("Z");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckez() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("z");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeX() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("X");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckex() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("x");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeC() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("C");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckec() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("c");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeV() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("V");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckev() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("v");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeB() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("B");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeb() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("b");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeN() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("N");
		textElement->setzeText(text);
	}
}
void Tastatur::druecken() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("n");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeM() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("M");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckem() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("m");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeKleinerAls() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("<");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeKomma() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append(",");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeGroesserAls() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append(">");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckePunkt() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append(".");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeFragezeichen() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("?");
		textElement->setzeText(text);
	}
}
void Tastatur::drueckeSlash() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append("/");
		textElement->setzeText(text);
	}
}
/*void Tastatur::drueckeAe() {
 TextElement *textElement =
 dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
 if (textElement != 0) {
 string text = textElement->gebeText();
 text.append("Ä");
 textElement->setzeText(text);
 }
 }
 void Tastatur::drueckeae() {
 TextElement *textElement =
 dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
 if (textElement != 0) {
 string text = textElement->gebeText();
 text.append("ä");
 textElement->setzeText(text);
 }
 }
 void Tastatur::drueckesz() {
 TextElement *textElement =
 dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
 if (textElement != 0) {
 string text = textElement->gebeText();
 text.append("ß");
 textElement->setzeText(text);
 }
 }*/

void Tastatur::drueckeGrossKlein() {
	Tastatur::gebeTastatur()->aendereGrossKlein();
}
void Tastatur::drueckeLeertaste() {
	TextElement *textElement =
			dynamic_cast<TextElement *>(GrafikHandler::gebeGrafikHandler()->gebeAusgewaehltesElement());
	if (textElement != 0) {
		string text = textElement->gebeText();
		text.append(" ");
		textElement->setzeText(text);
	}
}
