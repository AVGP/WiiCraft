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

#include "PaketManager.h"

#include <stddef.h>
#include <stdlib.h>
#include "PaketServer.h"
#include "../exception/ExcPaketUnbekanntesPaket.h"
#include "paket/Paket00KeepAlive.h"
#include "paket/Paket01LoginRequest.h"
#include "paket/Paket02Handshake.h"
#include "paket/Paket03ChatMessage.h"
#include "paket/Paket04TimeUpdate.h"
#include "paket/Paket05EntityEquipment.h"
#include "paket/Paket06SpawnPosition.h"
#include "paket/Paket08UpdateHealth.h"
#include "paket/Paket09Respawn.h"
#include "paket/Paket0DPlayerPositionLook.h"
#include "paket/Paket11UseBed.h"
#include "paket/Paket12Animation.h"
#include "paket/Paket14NamedEntitySpawn.h"
#include "paket/Paket15PickupSpawn.h"
#include "paket/Paket16CollectItem.h"
#include "paket/Paket17AddObjectVehicle.h"
#include "paket/Paket18MobSpawn.h"
#include "paket/Paket19EntityPainting.h"
#include "paket/Paket1AExperienceOrb.h"
#include "paket/Paket1CEntityVelocity.h"
#include "paket/Paket1DDestroyEntity.h"
#include "paket/Paket1EEntity.h"
#include "paket/Paket1FEntityRelativeMove.h"
#include "paket/Paket20EntityLook.h"
#include "paket/Paket21EntityLookAndRelativeMove.h"
#include "paket/Paket22EntityTeleport.h"
#include "paket/Paket23EntityHeadLook.h"
#include "paket/Paket26EntityStatus.h"
#include "paket/Paket27AttachEntity.h"
#include "paket/Paket28EntityMetadata.h"
#include "paket/Paket29EntityEffect.h"
#include "paket/Paket2ARemoveEntityEffect.h"
#include "paket/Paket2BExperience.h"
#include "paket/Paket32PreChunk.h"
#include "paket/Paket33MapChunk.h"
#include "paket/Paket34MultiBlockChange.h"
#include "paket/Paket35BlockChange.h"
#include "paket/Paket36BlockAction.h"
#include "paket/Paket3CExplosion.h"
#include "paket/Paket3DSoundParticleEffect.h"
#include "paket/Paket46NewInvalidState.h"
#include "paket/Paket47Thunderbolt.h"
#include "paket/Paket64OpenWindow.h"
#include "paket/Paket65CloseWindow.h"
#include "paket/Paket67SetSlot.h"
#include "paket/Paket68WindowItems.h"
#include "paket/Paket69UpdateWindowProperty.h"
#include "paket/Paket6ATransaction.h"
#include "paket/Paket6BCreativeInventoryAction.h"
#include "paket/Paket82UpdateSign.h"
#include "paket/Paket83ItemData.h"
#include "paket/Paket84UpdateTileEntity.h"
#include "paket/PaketC8IncrementStatistic.h"
#include "paket/PaketC9PlayerListItem.h"
#include "paket/PaketCAPlayerAbilities.h"
#include "paket/PaketFAPluginmessage.h"
#include "paket/PaketFFDisconnectKick.h"
#include "paket/PaketDummy.h"

using namespace std;

PaketServer **PaketManager::paketListe = NULL;

void PaketManager::registrierePaket(PaketServer *paket) {
	delete PaketManager::paketListe[paket->gebePaketId()];
	PaketManager::paketListe[paket->gebePaketId()] = paket;
}

void PaketManager::initialisierePaketListe() {
	PaketManager::paketListe = (PaketServer **) malloc(
			sizeof(PaketServer *) * 256);

	for (short i = 0; i < 256; i++) {
		PaketManager::paketListe[i] = new PaketDummy();
	}

	Paket00KeepAlive::registierePaket();
	Paket01LoginRequest::registierePaket();
	Paket02Handshake::registierePaket();
	Paket03ChatMessage::registierePaket();
	Paket04TimeUpdate::registierePaket();
	Paket05EntityEquipment::registierePaket();
	Paket06SpawnPosition::registierePaket();
	Paket08UpdateHealth::registierePaket();
	Paket09Respawn::registierePaket();
	Paket0DPlayerPositionLook::registierePaket();
	Paket11UseBed::registierePaket();
	Paket12Animation::registierePaket();
	Paket14NamedEntitySpawn::registierePaket();
	Paket15PickupSpawn::registierePaket();
	Paket16CollectItem::registierePaket();
	Paket17AddObjectVehicle::registierePaket();
	Paket18MobSpawn::registierePaket();
	Paket19EntityPainting::registierePaket();
	Paket1AExperienceOrb::registierePaket();
	Paket1CEntityVelocity::registierePaket();
	Paket1DDestroyEntity::registierePaket();
	Paket1EEntity::registierePaket();
	Paket1FEntityRelativeMove::registierePaket();
	Paket20EntityLook::registierePaket();
	Paket21EntityLookAndRelativeMove::registierePaket();
	Paket22EntityTeleport::registierePaket();
	Paket23EntityHeadLook::registierePaket();
	Paket26EntityStatus::registierePaket();
	Paket27AttachEntity::registierePaket();
	Paket28EntityMetadata::registierePaket();
	Paket29EntityEffect::registierePaket();
	Paket2ARemoveEntityEffect::registierePaket();
	Paket2BExperience::registierePaket();
	Paket32PreChunk::registierePaket();
	Paket33MapChunk::registierePaket();
	Paket34MultiBlockChange::registierePaket();
	Paket35BlockChange::registierePaket();
	Paket36BlockAction::registierePaket();
	Paket3CExplosion::registierePaket();
	Paket3DSoundParticleEffect::registierePaket();
	Paket46NewInvalidState::registierePaket();
	Paket47Thunderbolt::registierePaket();
	Paket64OpenWindow::registierePaket();
	Paket65CloseWindow::registierePaket();
	Paket67SetSlot::registierePaket();
	Paket68WindowItems::registierePaket();
	Paket69UpdateWindowProperty::registierePaket();
	Paket6ATransaction::registierePaket();
	Paket6BCreativeInventoryAction::registierePaket();
	Paket82UpdateSign::registierePaket();
	Paket83ItemData::registierePaket();
	Paket84UpdateTileEntity::registierePaket();
	PaketC8IncrementStatistic::registierePaket();
	PaketC9PlayerListItem::registierePaket();
	PaketCAPlayerAbilities::registierePaket();
	PaketFAPluginmessage::registierePaket();
	PaketFFDisconnectKick::registierePaket();
}

PaketServer *PaketManager::getInstanz(byte byte) {
	PaketDummy *paketServer =
			dynamic_cast<PaketDummy *>(PaketManager::paketListe[byte]);
	if (paketServer != 0) {
		throw ExcPaketUnbekanntesPaket(byte);
	}

	return PaketManager::paketListe[byte]->gebeInstanz();
}
