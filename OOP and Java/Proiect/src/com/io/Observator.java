package com.io;

import com.pokemon.Pokemon;

// Acest observer scrie in log in momentul in care un pokemon este stunned sau da dodge
// Observer-ul are ca subiect un pokemon, si este notificat atunci cand subiectul
// isi schimba starea (campul de dodge sau stunned)
public class Observator {
    Pokemon subiect;

    public Observator(Pokemon subiect){
        this.subiect = subiect;
        this.subiect.attachObservator(this);
    }

    public void notificaStun(){
        if(!subiect.isStunned())
            Logger.logAction(subiect, " is stunned!");
    }

    public void notificaDodge(){
        if(!subiect.isDodging())
            Logger.logAction(subiect, " dodged!");
    }
}
