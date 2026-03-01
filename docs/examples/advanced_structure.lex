// Esempio avanzato: Struttura con condizioni, eventi e UI
// Questo file mostra tutte le feature principali di Lex

struttura FabbricaVapore {
    // Metadati base
    era: Steampunk
    nome: "Fabbrica a Vapore"
    descrizione: "Il cuore pulsante dell'industria steampunk"
    
    // Costi e produzione
    costo: {
        Carbone: 8,
        Acciaio: 5,
        Oro: 50
    }
    
    produzione: {
        Energia: 15,
        Industria: 10
    }
    
    mantenimento: {
        Carbone: 2,
        Oro: 5
    }
    
    // Requisiti (riferimenti ad altre definizioni)
    requisiti: {
        tecnologie: [MotoreVapore],
        strutture: [FonderiaDiAcciaio]
    }
    
    // Sblocca altro contenuto
    sblocca: {
        tecnologie: [MotoreVaporeAvanzato, ZeppelinDaTrasporto],
        strutture: [OfficinaMeccanica]
    }
    
    // Condizioni di disponibilità
    disponibile_se {
        // La struttura è disponibile solo se...
        condizione: civiltà.industria_totale >= 100,
        
        messaggio: "La tua industria è abbastanza sviluppata per una fabbrica a vapore"
    }
    
    // Eventi speciali (segreti, achievement, etc.)
    eventi: {
        // Segreto: se costruita in tutte le città
        segreto_se {
            condizione: civiltà.ha_struttura_in_ogni_città(FabbricaVapore),
            
            attiva: ConspirazioneIndustriale,
            
            archivista: "Qualcuno sta raccogliendo troppo potere nelle fabbriche..."
        }
        
        // Bonus: se costruita vicino a un fiume
        bonus_se {
            condizione: mappa.tile_corrente.ha_fiume,
            
            effetto: {
                produzione: { Energia: +5 }  // +33% produzione energia
            },
            
            notifica: "Il fiume alimenta le caldaie della fabbrica!"
        }
    }
    
    // UI e Visualizzazione
    ui: {
        icona: "assets/steampunk/fabbrica_vapore.png",
        colore: #8B6914,  // Bronzo industriale
        
        tooltip: {
            titolo: "Fabbrica a Vapore",
            descrizione: "Converte carbone in energia e produzione industriale",
            
            stats: [
                "Produzione Energia: +15",
                "Produzione Industria: +10",
                "Mantenimento: 2 Carbone/turno, 5 Oro/turno"
            ],
            
            requisiti: [
                "Era: Steampunk",
                "Tech: Motore a Vapore",
                "Struttura: Fonderia di Acciaio"
            ]
        },
        
        pannello: {
            componenti: [
                "ResourceFlow",      // Mostra input/output
                "ProductionGraph",   // Grafico produzione over time
                "MaintenanceCost"    // Costi mantenimento
            ],
            
            azioni: [
                { nome: "Potenzia", icona: "upgrade", azione: "upgrade_building" },
                { nome: "Disattiva", icona: "pause", azione: "toggle_building" },
                { nome: "Demolisci", icona: "destroy", azione: "destroy_building" }
            ]
        }
    }
    
    // Lore e AI Context
    lore: {
        citazione: "Il vapore trasforma il ferro in potere — dixit Brunel",
        
        descrizione: "
            Le fabbriche a vapore rappresentano il cuore dell'era industriale.
            Convertono carbone in energia meccanica, alimentando macchinari
            complessi e produzioni di massa.
        ",
        
        contesto_ai: "
            IMPORTANTE: Questa struttura è critica per l'era Steampunk.
            Il giocatore dovrebbe costruire almeno una fabbrica per città.
            Se ha troppe fabbriche senza sufficiente carbone, avrà problemi economici.
            Suggerisci espansione miniere carbone se produzione < consumo.
        ",
        
        riferimenti_storici: [
            "Revoluzione Industriale Inglese (1760-1840)",
            "Isambard Kingdom Brunel - ingegnere vittoriano",
            "Steam engine - James Watt"
        ]
    }
    
    // Integrazione sistemi
    integrazioni: {
        // Sistema Economico
        economia: {
           mercato: {
                domanda: { Carbone: +20 },  // Aumenta domanda carbone
                offerta: { Energia: +15 }   // Aumenta offerta energia
            }
        },
        
        // Sistema Sociale
        societa: {
            impiego: 50,  // Crea 50 posti lavoro
            salute: -2,   // Inquina, -2 salute
            felicità: -1  // Rumore, -1 felicità
        },
        
        // Sistema Militare
        militare: {
            supporto_unità: ["TankVapore", "Zeppelin"]  // Supporta queste unità
        }
    }
}

---

// Come viene compilato:

// → scripts/lua/buildings/fabbrica_vapore.lua
//    (logica gameplay: condizioni, eventi, integrazioni)

// → data/buildings/fabbrica_vapore.json
//    (dati statici: costi, produzione, stats)

// → ui/buildings/FabbricaVaporePanel.tsx
//    (componente React per UI)

// → ai/lore/buildings/fabbrica_vapore.txt
//    (contesto per LLM companion)

// → engine/bindings/buildings_fabbrica_vapore.cpp (opzionale)
//    (binding C++ per integrazione diretta)
