// Esempio: Definizione completa di un'Era
// Questo file mostra come definire un'era con strutture, tecnologie, scelte e finali

era Steampunk {
    // Metadati era
    nome: "Era Steampunk"
    periodo: "1850-1900"
    descrizione: "L'età del vapore, dell'ingegneria meccanica e della rivoluzione industriale"
    
    atmosfera: "industriale, nebbiosa, meccanica"
    musica: "steampunk_ost"
    colore_dominante: #8B6914  // Bronzo
    
    // Transizione era
    transizione: {
        richiesta: {
            tecnologie_minime: 12,
            risorse: { Energia: 1000, Industria: 500 }
        },
        
        cinematica: "CinematicaSteampunkTransition",
        
        archivista: "
            L'odore di carbone e olio riempie l'aria.
            Una nuova era è iniziata — l'era delle macchine.
        "
    }
    
    // === STRUTTURE DELL'ERA ===
    strutture: {
        FabbricaVapore: {
            // ... (vedi advanced_structure.lex per dettagli)
        }
        
        OfficinaMeccanica: {
            era: Steampunk
            costo: { Acciaio: 10, Oro: 80 }
            produzione: { Industria: 8, Tecnologia: 3 }
            requisiti: { strutture: [FabbricaVapore] }
            sblocca: { unità: [TankVapore, AeronaveCorazzata] }
        }
        
        RaffineriaCarbone: {
            era: Steampunk
            costo: { Pietra: 15, Oro: 60 }
            produzione: { Carbone: 10 }
            
            bonus_se: {
                condizione: mappa.tile_corrente.ha_risorsa(GiacimentoCarbone),
                effetto: { produzione: { Carbone: +10 } }  // 100% bonus
            }
        }
        
        StazioneTelegrafo: {
            era: Steampunk
            costo: { Rame: 5, Oro: 40 }
            produzione: { Comunicazione: 5 }
            
            effetto_globale: {
                velocità_truppe: +10%,  // Comunicazione veloce
                commercio_efficienza: +15%
            }
        }
    }
    
    // === TECNOLOGIE DELL'ERA ===
    tecnologie: {
        MotoreVapore: {
            era: Steampunk
            nome: "Motore a Vapore"
            costo_ricerca: 450
            
            prerequisiti: [Metallurgia, TermodinamicaBase]
            
            sblocca: {
                strutture: [FabbricaVapore, OfficinaMeccanica],
                unità: [TrenoCorazzato],
                bonus: ["Produzione industriale +25%"]
            }
            
            citazione: "Il vapore trasforma il ferro in potere — dixit Brunel"
        }
        
        Elettromagnetismo: {
            era: Steampunk
            nome: "Elettromagnetismo"
            costo_ricerca: 600
            
            prerequisiti: [MotoreVapore, MatematicaAvanzata]
            
            sblocca: {
                tecnologie: [Telegrafo, DinamoElettrica],
                strutture: [StazioneTelegrafo, CentraleElettrica]
            }
            
            citazione: "La scienza è la chiave del futuro"
        }
        
        Aeronavigazione: {
            era: Steampunk
            nome: "Aeronavigazione"
            costo_ricerca: 750
            
            prerequisiti: [MotoreVapore, Aerodinamica]
            
            sblocca: {
                unità: [Zeppelin, DirigibileDaGuerra],
                strutture: [HangarZeppelin]
            }
            
            citazione: "Non ci sono più confini — solo orizzonti"
        }
    }
    
    // === UNITÀ DELL'ERA ===
    unità: {
        TankVapore: {
            era: Steampunk
            tipo: militare
            
            statistiche: {
                attacco: 25,
                difesa: 20,
                movimento: 3
            }
            
            costo: { Acciaio: 15, Carbone: 8, Oro: 150 }
            mantenimento: { Carbone: 2, Oro: 8 }
            
            abilità: [Sfondamento, Corazzato]
            requisiti: { tecnologie: [MotoreVapore] }
        }
        
        Zeppelin: {
            era: Steampunk
            tipo: esploratore
            
            statistiche: {
                attacco: 5,
                difesa: 8,
                movimento: 8,
                portata: 4  // Ranged
            }
            
            costo: { Acciaio: 10, Idrogeno: 20, Oro: 200 }
            mantenimento: { Idrogeno: 3, Oro: 10 }
            
            abilità: [Ricognizione, BombardamentoLeggero]
            requisiti: { tecnologie: [Aeronavigazione] }
        }
    }
    
    // === SCELTE NARRATIVE DELL'ERA ===
    scelte: {
        RivoluzioneOperaia: {
            era: Steampunk
            
            trigger: {
                condizione: civiltà.popolazione > 100 AND civiltà.felicità < 40,
                probabilità: 30%
            }
            
            testo: "
                I lavoratori delle fabbriche si stanno organizzando.
                Chiedono migliori condizioni di lavoro e salari più alti.
                Come rispondi?
            "
            
            opzioni: {
                Sopprimere: {
                    testo: "Schiaccia il movimento operaio con la forza"
                    
                    effetto: {
                        Industria: +30,
                        Felicità: -20,
                        Salute: -5
                    }
                    
                    flag: flag_rivoluzione_soppressa
                    
                    archivista: "
                        Hai scelto la via del ferro.
                        La pace sociale è mantenuta, ma a quale prezzo?
                    "
                }
                
                Negare: {
                    testo: "Rifiuta le richieste, ma evita la violenza"
                    
                    effetto: {
                        Felicità: -10,
                        RivoltaRischio: +40%  // Aumenta rischio rivolte future
                    }
                    
                    archivista: "
                        I lavoratori non dimenticheranno questo rifiuto.
                        La tensione continua a crescere.
                    "
                }
                
                Assecondare: {
                    testo: "Accetta le richieste dei lavoratori"
                    
                    effetto: {
                        Felicità: +25,
                        Industria: -10,
                        Oro: -200
                    }
                    
                    flag: flag_diritti_lavoratori
                    
                    archivista: "
                        Hai fatto la scelta giusta.
                        I tuoi cittadini lavoreranno meglio, sapendo di essere ascoltati.
                    "
                }
            }
        }
    }
    
    // === FINALI DELL'ERA (segreti) ===
    finali: {
        ConspirazioneIndustriale: {
            tipo: segreto
            
            trigger: {
                condizione: civiltà.ha_struttura_in_ogni_città(FabbricaVapore),
                era: Steampunk,
                flag: flag_rivoluzione_soppressa
            }
            
            cinematica: "CinematicaConspiracy"
            
            testo: "
                Le fabbriche che hai costruito per rafforzare il tuo potere
                sono diventate la tua gabbia. I capitalisti che hai favorito
                ora controllano l'economia — e presto, il governo.
            "
            
            effetto: {
                sblocca: [Ending_CapitalismoSenzaControllo],
                disabilita: [DemocraziaSindacale]
            }
            
            archivista: "
                Ho visto molti finali. Questo... non lo avevo previsto.
                Il potere economico è diventato potere politico.
            "
        }
    }
}

---

// Questo file genera:
// → scripts/lua/eras/steampunk_era.lua         (logica era completa)
// → data/eras/steampunk.json                   (dati statici)
// → ui/panels/SteampunkEraPanel.tsx           (UI panel)
// → ai/lore/eras/steampunk_context.txt        (AI context)
// → data/technologies/steampunk_techs.json    (tecnologie)
// → data/units/steampunk_units.json           (unità)
// → data/structures/steampunk_structures.json (strutture)
// → scripts/lua/events/steampunk_events.lua   (eventi e scelte)
