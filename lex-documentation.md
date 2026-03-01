# Lex — Il Linguaggio di Imperium

> *"Descrivi il mondo, non come costruirlo."*

Lex è il linguaggio ufficiale per estendere e modificare **Imperium**. Progettato per essere leggibile come prosa, potente come codice, e accessibile a tutti — dal modder curioso al developer esperto.

---

## Indice

1. [Cos'è Lex](#cosè-lex)
2. [Guida Rapida — 10 minuti](#guida-rapida--10-minuti)
3. [Concetti Fondamentali](#concetti-fondamentali)
   - [Ere](#ere)
   - [Strutture](#strutture)
   - [Unità](#unità)
   - [Tecnologie](#tecnologie)
   - [Risorse](#risorse)
   - [Scelte e Condizioni](#scelte-e-condizioni)
   - [Finali](#finali)
   - [Il Companion — Archivista](#il-companion--archivista)
4. [Reference Completo](#reference-completo)
   - [Keyword](#keyword)
   - [Tipi di Dato](#tipi-di-dato)
   - [Operatori](#operatori)
   - [Errori Comuni](#errori-comuni)
5. [Cookbook](#cookbook)
   - [Come Creare una Struttura](#come-creare-una-struttura)
   - [Come Creare un Finale Segreto](#come-creare-un-finale-segreto)
   - [Come Collegare Scelte Attraverso le Ere](#come-collegare-scelte-attraverso-le-ere)
   - [Come Far Reagire l'Archivista](#come-far-reagire-larchivista)
6. [Integrazione con Imperium](#integrazione-con-imperium)

---

## Cos'è Lex

Lex è un linguaggio **dichiarativo** — significa che descrivi *cosa esiste nel mondo di Imperium*, non come il motore lo deve eseguire. Questo lo rende intuitivo anche per chi non ha mai programmato.

```lex
// Questo è Lex. Si legge quasi come italiano.
struttura Acquedotto {
    era: Antica
    costo: [Pietra x4, Legno x2]
    produzione: [Acqua x5, Salute x2]
}
```

Lex compila verso il core di Imperium scritto in C++ e verso gli script Lua interni. Non devi sapere nulla di C++ o Lua — Lex si occupa di tutto.

### A chi è rivolto

Lex è pensato per tre tipi di utenti:

**Modder** — vuoi aggiungere nuove civiltà, strutture, unità o stravolgere le regole del gioco. Lex ti dà il pieno controllo senza toccare il codice sorgente di Imperium.

**Designer** — vuoi progettare nuove ere, eventi narrativi, dialoghi dell'Archivista, o finali alternativi. Con Lex puoi farlo in modo leggibile e strutturato.

**Sviluppatori** — vuoi estendere l'architettura di Imperium a livello di sistemi. Lex supporta anche definizioni di sistemi di gioco ad alto livello.

### Filosofia

Tre principi guidano Lex:

**Semplicità prima di tutto.** Se una cosa si può scrivere in modo più semplice, quella è la sintassi corretta.

**Il contesto è tutto.** In Lex i blocchi sono annidati — la struttura del codice rispecchia la struttura del gioco.

**Gli errori spiegano, non accusano.** Ogni errore di Lex ti dice cosa correggere, non solo cosa è andato storto.

---

## Guida Rapida — 10 minuti

### Passo 1 — La tua prima struttura

Crea un file chiamato `mia_mod.lex` e scrivi:

```lex
struttura TorreDiGuardia {
    era: Medievale
    costo: [Pietra x6, Legno x3]
    produzione: [Difesa x8]
    descrizione: "Una torre che veglia sui confini del regno"
}
```

Salva il file nella cartella `/mods` di Imperium. La struttura apparirà automaticamente nel gioco durante l'era Medievale.

### Passo 2 — La tua prima condizione

Le condizioni rendono il gioco reattivo alle scelte del giocatore:

```lex
struttura FortezzaImperiale {
    era: Medievale
    costo: [Pietra x20, Ferro x10]
    produzione: [Difesa x30, Prestigio x5]
    
    disponibile se civiltà.strutture_costruite >= 10 {
        messaggio: "Il tuo impero è abbastanza grande per una fortezza"
    }
}
```

### Passo 3 — Il tuo primo evento

Gli eventi reagiscono a quello che succede nel gioco:

```lex
evento PrimeNavi {
    era: Rinascimentale
    
    quando civiltà.ha_tecnologia(Navigazione) {
        testo: "Le tue caravelle solcano mari inesplorati"
        effetto: [Commercio +15, Esplorazione +20]
        archivista: "I tuoi marinai stanno riscrivendo le mappe del mondo"
    }
}
```

In tre passi hai già creato una struttura, una condizione e un evento. Questo è Lex.

---

## Concetti Fondamentali

### Ere

Le ere sono i contenitori principali del gioco. Ogni contenuto in Lex appartiene a un'era. Imperium ha 8 ere predefinite, ma puoi aggiungere le tue.

```lex
era NomeDellEra {
    atmosfera: "descrizione dell'atmosfera"
    musica: nome_del_file_audio
    colore_dominante: #RRGGBB
    
    // Tutto ciò che definisci qui appartiene a questa era
}
```

**Le 8 ere di Imperium:**

| ID Interno | Nome Visualizzato | Periodo |
|---|---|---|
| `PietràAntica` | Età della Pietra | Preistoria |
| `Antica` | Era Antica | Grecia e Roma |
| `Medievale` | Era Medievale | Medioevo |
| `Rinascimentale` | Era Rinascimentale | Rinascimento Italiano |
| `Steampunk` | Era Steampunk | Vapore e Ingranaggi |
| `Moderna` | Era Moderna | XX Secolo |
| `Atompunk` | Era Atompunk | Bunker e Sopravvivenza |
| `Cyber` | Era Cyber/Trascendenza | Futuro |

```lex
// Esempio: definire contenuto per l'era Steampunk
era Steampunk {
    atmosfera: "industriale, nebbiosa, meccanica"
    musica: steampunk_ost
    colore_dominante: #8B6914
    
    struttura FabbricaVapore {
        // ...
    }
}
```

---

### Strutture

Le strutture sono gli edifici e le installazioni che il giocatore costruisce nella capitale e nelle città espanse.

```lex
struttura NomeStruttura {
    era: NomeDellEra              // Era in cui è disponibile
    costo: [Risorsa x Quantità]   // Costo di costruzione
    produzione: [Risorsa x Quantità] // Cosa produce ogni turno
    requisiti: [AltraStruttura]   // Strutture necessarie prima
    sblocca: [Tecnologia]         // Cosa sblocca dopo la costruzione
    descrizione: "testo"          // Testo mostrato nel gioco
    
    // Opzionale: condizioni speciali
    disponibile se condizione {
        // logica
    }
    
    segreto se condizione {
        // evento segreto
    }
}
```

**Esempio completo:**

```lex
struttura OficinaVapore {
    era: Steampunk
    costo: [Carbone x8, Acciaio x5, Oro x50]
    produzione: [Energia x15, Industria x10]
    requisiti: [FonderiaDiAcciaio]
    sblocca: [MotoreVaporeAvanzato, ZeppelinDaTrasporto]
    descrizione: "Il cuore pulsante dell'industria steampunk"
    
    segreto se civiltà.ufficina_vapore_in_tutte_le_città {
        attiva: ConspirazioneIndustriale
        archivista: "Qualcuno sta raccogliendo troppo potere..."
    }
}
```

---

### Unità

Le unità sono le forze militari, gli esploratori, i diplomatici e i personaggi speciali del gioco.

```lex
unità NomeUnità {
    era: NomeDellEra
    tipo: militare | esploratore | diplomatico | speciale
    costo: [Risorsa x Quantità]
    mantenimento: [Risorsa x Quantità]  // Costo ogni turno
    
    statistiche {
        attacco: valore
        difesa: valore
        movimento: valore
        portata: valore        // Solo per unità a distanza
    }
    
    abilità: [NomeAbilità]
    requisiti: [Tecnologia]
    descrizione: "testo"
}
```

**Esempio:**

```lex
unità AeronaveCorazzata {
    era: Steampunk
    tipo: militare
    costo: [Acciaio x20, Carbone x10, Oro x200]
    mantenimento: [Carbone x3, Oro x10]
    
    statistiche {
        attacco: 45
        difesa: 30
        movimento: 6
        portata: 3
    }
    
    abilità: [BombardamentoAereo, RicognizioneTattica]
    requisiti: [TecnologiaAeronavi]
    descrizione: "Il terrore dei cieli industriali"
}
```

---

### Tecnologie

Le tecnologie formano l'albero della ricerca. Ogni era ha il suo ramo tecnologico.

```lex
tecnologia NomeTecnologia {
    era: NomeDellEra
    costo_ricerca: valore
    requisiti: [AltraTecnologia]
    
    sblocca {
        strutture: [NomeStruttura]
        unità: [NomeUnità]
        bonus: [Descrizione effetto]
    }
    
    descrizione: "testo"
    citazione: "frase storica o evocativa"
}
```

**Esempio:**

```lex
tecnologia MotoreVapore {
    era: Steampunk
    costo_ricerca: 450
    requisiti: [Metallurgia, TermodinamicaBase]
    
    sblocca {
        strutture: [FabbricaVapore, OficinaVapore]
        unità: [TremoAutoblindato]
        bonus: ["Produzione industriale +25% in tutte le città"]
    }
    
    descrizione: "Il vapore trasforma il ferro in potere"
    citazione: "La macchina a vapore è il cavallo del futuro — dixit Brunel"
}
```

---

### Risorse

Definisci risorse custom per la tua mod o consulta le risorse native di Imperium.

```lex
risorsa NomeRisorsa {
    tipo: base | strategica | di_lusso | speciale
    icona: percorso/icona.png
    colore: #RRGGBB
    descrizione: "testo"
    
    // Come viene prodotta
    prodotta_da: [Struttura, Terreno]
    
    // Effetti globali se abbondante
    effetto_abbondanza: "descrizione effetto"
    
    // Effetti se mancante
    effetto_scarsità: "descrizione effetto"
}
```

**Risorse native di Imperium — Era Steampunk:**

| Risorsa | Tipo | Uso Principale |
|---|---|---|
| `Carbone` | Strategica | Energia, Industria |
| `Acciaio` | Strategica | Strutture, Unità |
| `Vapore` | Speciale | Tecnologie avanzate |
| `Etere` | Di Lusso | Benessere, Segreti |

---

### Scelte e Condizioni

Le scelte sono il cuore narrativo di Imperium — determinano i finali e sbloccano segreti.

```lex
scelta NomeScelta {
    disponibile: era.NomeDellEra
    condizione: espressione_booleana
    
    testo: "Domanda mostrata al giocatore"
    
    opzione A {
        testo: "Prima opzione"
        effetto: {
            // cosa succede
        }
        segna: flag_narrativo_A
    }
    
    opzione B {
        testo: "Seconda opzione"
        effetto: {
            // cosa succede
        }
        segna: flag_narrativo_B
    }
}
```

**Esempio — La grande guerra:**

```lex
scelta TensioneGlobale {
    disponibile: era.Moderna
    condizione: tensione_globale > 85
    
    testo: "La tensione tra le nazioni è al limite. Come procedi?"
    
    opzione Diplomazia {
        testo: "Cerca un accordo diplomatico di emergenza"
        effetto: {
            tensione_globale -= 30
            relazioni_internazionali += 20
        }
        segna: flag_scelta_pace
    }
    
    opzione Guerra {
        testo: "Lancia l'offensiva finale"
        effetto: {
            transizione -> era.Atompunk
            distruggi: strutture_superficie
            attiva: BunkerProtocol
        }
        segna: flag_guerra_nucleare
    }
}
```

#### Operatori per le condizioni

```lex
// Confronto numerico
tensione_globale > 85
civiltà.popolazione >= 1000000
civiltà.oro < 100

// Controllo flag
civiltà.ha_flag(flag_guerra_nucleare)
non civiltà.ha_flag(flag_scelta_pace)

// Controllo risorse e strutture
civiltà.ha_tecnologia(MotoreVapore)
civiltà.ha_struttura(FabbricaVapore)
civiltà.strutture_costruite >= 10

// Era corrente
era.corrente == Steampunk
era.completata(Medievale)

// Combinazioni logiche
tensione_globale > 85 e civiltà.ha_flag(flag_guerra_iniziata)
civiltà.ha_tecnologia(Navigazione) o civiltà.ha_struttura(Porto)
```

---

### Finali

I finali sono i punti di arrivo del gioco. Possono essere canonici, segreti, o negativi.

```lex
finale NomeFinale {
    tipo: canonico | segreto | negativo
    
    requisiti {
        era: NomeDellEra
        tecnologie: [Lista]
        risorse: [Lista con quantità]
        strutture: [Lista]
        storia: espressione_flag   // flag narrativi richiesti
    }
    
    sequenza: NomeCinematica
    musica: nome_file_audio
    testo: "Testo narrativo del finale"
    archivista: "Cosa dice l'Archivista alla fine"
}
```

**I due finali canonici di Imperium:**

```lex
finale TerraRinata {
    tipo: canonico
    
    requisiti {
        era: Cyber
        tecnologie: [PurificazioneAtmosferica, NanobotEcologici]
        risorse: [EnergiaOscura x200]
        storia: non civiltà.ha_flag(flag_genocidio)
    }
    
    sequenza: CinematicaTerraVerde
    musica: finale_speranza_ost
    testo: "Hai scelto di rimanere. La Terra è tua da ricostruire."
    archivista: "Questo pianeta ha visto l'alba di molte civiltà. 
                 Ora tocca a te scrivere l'ultimo capitolo."
}

finale Aurora {
    tipo: canonico
    
    requisiti {
        era: Cyber
        tecnologie: [PropulsioneAntimaterica, ScudoPlanetario, CriostasiBiologica]
        risorse: [Iridio x100, EnergiaOscura x500, AntimateriaStabile x50]
        strutture: [MotoreAuroraCompletato]
        storia: non civiltà.ha_flag(flag_genocidio)
    }
    
    sequenza: CinematicaPartenza
    musica: aurora_ost
    testo: "L'Aurora si solleva lentamente dalla Terra. 
            Sotto di voi, il pianeta si rimpicciolisce fino a diventare un punto azzurro.
            Davanti a voi — l'infinito."
    archivista: "Ho custodito la memoria di tutto ciò che è stato. 
                 Ora custodirò anche questo momento — il giorno in cui 
                 l'umanità ha toccato le stelle."
}
```

---

### Il Companion — Archivista

L'Archivista è il companion AI del gioco — conosce la storia della tua civiltà e reagisce alle tue scelte. In Lex puoi definire le sue risposte e i suoi interventi.

```lex
companion Archivista {
    conosce: [ere, scelte_giocatore, segreti_sbloccati, tecnologie, strutture]
    
    // Intervento all'ingresso in una nuova era
    quando giocatore.entra(era.NomeDellEra) {
        dice: "testo del messaggio"
        lore: file_lore.era
        tono: neutro | entusiasta | cupo | misterioso
    }
    
    // Intervento su una scelta specifica
    quando giocatore.compie_scelta(NomeScelta) {
        prima {
            dice: "testo prima della scelta"
        }
        dopo_opzione_A {
            dice: "testo se sceglie A"
        }
        dopo_opzione_B {
            dice: "testo se sceglie B"
        }
    }
    
    // Intervento su un segreto sbloccato
    quando segreto_attivato(NomeSegreto) {
        dice: "testo"
        tono: misterioso
    }
}
```

**Esempio:**

```lex
companion Archivista {
    conosce: [ere, scelte_giocatore, segreti_sbloccati, tecnologie]
    
    quando giocatore.entra(era.Steampunk) {
        dice: "L'odore di carbone e olio riempie l'aria. 
               Una nuova era è iniziata — l'era delle macchine."
        lore: lore_steampunk.intro
        tono: neutro
    }
    
    quando giocatore.entra(era.Atompunk) {
        dice: "Il silenzio fuori dai bunker è assordante. 
               Il mondo che conoscevi non esiste più. 
               Ma voi siete ancora qui."
        lore: lore_atompunk.sopravvivenza
        tono: cupo
    }
    
    quando giocatore.compie_scelta(TensioneGlobale) {
        prima {
            dice: "Ogni civiltà nella storia ha affrontato questo momento.
                   Poche hanno scelto bene."
        }
        dopo_opzione_Guerra {
            dice: "Hai scelto. Ora dovrai vivere con questa scelta — 
                   se vivere è ancora la parola giusta."
            tono: cupo
        }
    }
}
```

---

## Reference Completo

### Keyword

| Keyword | Descrizione |
|---|---|
| `era` | Definisce un'era storica |
| `struttura` | Definisce un edificio costruibile |
| `unità` | Definisce un'unità militare o speciale |
| `tecnologia` | Definisce una tecnologia ricercabile |
| `risorsa` | Definisce una risorsa custom |
| `scelta` | Definisce un evento decisionale |
| `finale` | Definisce un finale del gioco |
| `segreto` | Definisce un evento segreto |
| `evento` | Definisce un evento narrativo |
| `companion` | Configura il comportamento dell'Archivista |
| `quando` | Definisce un trigger condizionale |
| `se` | Condizione inline |
| `disponibile` | Condizione di disponibilità |
| `attiva` | Attiva un evento o segreto |
| `transizione` | Forza il passaggio a un'altra era |
| `segna` | Imposta un flag narrativo |
| `distruggi` | Rimuove strutture o elementi dal gioco |
| `sblocca` | Rende disponibile qualcosa |
| `produzione` | Definisce output periodico |
| `costo` | Definisce il costo di costruzione |
| `requisiti` | Prerequisiti necessari |

### Tipi di Dato

| Tipo | Esempio | Descrizione |
|---|---|---|
| `Testo` | `"ciao mondo"` | Stringhe di testo |
| `Numero` | `42`, `3.14` | Valori numerici |
| `Booleano` | `vero`, `falso` | Valore logico |
| `Colore` | `#8B6914` | Colore esadecimale |
| `Lista` | `[Pietra x4, Legno x2]` | Lista di elementi |
| `Flag` | `flag_guerra_nucleare` | Marker narrativo |
| `Riferimento Era` | `era.Steampunk` | Riferimento a un'era |
| `File Audio` | `steampunk_ost` | Riferimento a file audio |
| `File Lore` | `lore_steampunk.intro` | Riferimento a file lore |

### Operatori

**Confronto:**

```lex
>    // maggiore di
<    // minore di
>=   // maggiore o uguale
<=   // minore o uguale
==   // uguale
!=   // diverso
```

**Logici:**

```lex
e    // AND logico
o    // OR logico
non  // NOT logico
```

**Assegnazione ed effetti:**

```lex
+=   // incrementa
-=   // decrementa
=    // assegna
->   // transizione verso
```

**Quantità nelle liste:**

```lex
Risorsa x Quantità    // esempio: Pietra x4
```

### Errori Comuni

**Errore: Risorsa non trovata**
```
LEX_ERR_001: Risorsa "Adamantio" non trovata.
Suggerimento: Verifica il nome nella lista delle risorse native o definiscila con 'risorsa Adamantio { ... }'
```

**Errore: Era non valida**
```
LEX_ERR_002: Era "Futuristica" non riconosciuta.
Suggerimento: Le ere valide sono: PietràAntica, Antica, Medievale, Rinascimentale, Steampunk, Moderna, Atompunk, Cyber
```

**Errore: Condizione mal formata**
```
LEX_ERR_003: Condizione non valida alla riga 14.
Suggerimento: Le condizioni devono avere la forma 'variabile operatore valore'. Esempio: 'tensione_globale > 85'
```

**Errore: Blocco non chiuso**
```
LEX_ERR_004: Blocco 'struttura FabbricaVapore' aperto ma mai chiuso.
Suggerimento: Assicurati che ogni '{' abbia il corrispondente '}'
```

---

## Cookbook

### Come Creare una Struttura

**Caso semplice — struttura base:**

```lex
struttura MercatoMedievale {
    era: Medievale
    costo: [Legno x5, Pietra x3, Oro x30]
    produzione: [Commercio x8, Felicità x2]
    descrizione: "Un vivace mercato che anima la città"
}
```

**Caso avanzato — struttura con prerequisiti e segreto:**

```lex
struttura GuildaDeiMercanti {
    era: Rinascimentale
    costo: [Legno x8, Pietra x5, Oro x150]
    produzione: [Commercio x20, Diplomazia x5]
    requisiti: [MercatoMedievale, PortoCittadino]
    sblocca: [VieSericaPrivata, BancaMedicea]
    descrizione: "La guilda che controlla i commerci del Rinascimento"
    
    disponibile se civiltà.commercio_totale >= 50 {
        messaggio: "Le tue rotte commerciali sono abbastanza forti per una guilda"
    }
    
    segreto se civiltà.ha_struttura(GuildaDeiMercanti) e era.corrente == Steampunk {
        attiva: ConspirazioneEconomica
        archivista: "La guilda esiste ancora. E ha più potere di quanto pensi."
    }
}
```

---

### Come Creare un Finale Segreto

I finali segreti richiedono flag narrativi impostati durante il gioco. Pianifica prima quali scelte portano al segreto.

**Passo 1 — Imposta i flag nelle scelte:**

```lex
scelta AlleanzaSegreta {
    disponibile: era.Steampunk
    condizione: civiltà.ha_struttura(GuildaDeiMercanti)
    
    opzione Accetta {
        testo: "Stringi un'alleanza con le forze nell'ombra"
        effetto: { Oro += 500 }
        segna: flag_alleanza_oscura    // questo flag è la chiave
    }
}
```

**Passo 2 — Definisci il finale segreto:**

```lex
finale OrdineNascosto {
    tipo: segreto
    
    requisiti {
        era: Cyber
        storia: civiltà.ha_flag(flag_alleanza_oscura)
        tecnologie: [ControlloMentale, SurveillanceGlobale]
    }
    
    sequenza: CinematicaOrdine
    testo: "Non hai costruito un impero. Hai costruito una gabbia dorata per l'umanità.
            E l'umanità... ti ringrazierà."
    archivista: "Ho visto molti finali. Questo... non lo avevo previsto."
}
```

---

### Come Collegare Scelte Attraverso le Ere

Le scelte nell'era Steampunk possono influenzare eventi nell'era Cyber — questa è la memoria storica di Lex.

```lex
// Era Steampunk — la scelta iniziale
scelta RivoluzioneOperaia {
    disponibile: era.Steampunk
    
    opzione SopprimeRivoluzione {
        testo: "Schiaccia il movimento operaio"
        effetto: { Industria += 30, Felicità -= 20 }
        segna: flag_rivoluzione_soppressa
    }
    
    opzione AssecondarRivoluzione {
        testo: "Abbraccia i diritti dei lavoratori"
        effetto: { Felicità += 25, Industria -= 10 }
        segna: flag_diritti_lavoratori
    }
}

// Era Atompunk — conseguenza della scelta precedente
evento Eredità del Passato {
    era: Atompunk
    
    quando era.inizia e civiltà.ha_flag(flag_rivoluzione_soppressa) {
        testo: "Nei bunker, le vecchie tensioni riemergono.
                La memoria dell'oppressione è dura a morire."
        effetto: { Coesione_Sociale -= 15 }
        archivista: "La storia che ignori è quella che ti condanna a rivivere."
    }
    
    quando era.inizia e civiltà.ha_flag(flag_diritti_lavoratori) {
        testo: "Nei bunker, la comunità si stringe attorno ai valori
                che avete costruito insieme generazioni fa."
        effetto: { Coesione_Sociale += 20 }
        archivista: "Le scelte di chi vi ha preceduto vi proteggono ancora."
    }
}
```

---

### Come Far Reagire l'Archivista

L'Archivista può essere configurato per rispondere a praticamente qualsiasi evento del gioco.

```lex
companion Archivista {
    conosce: [ere, scelte_giocatore, segreti_sbloccati, tecnologie, strutture]
    
    // Reazione a una tecnologia scoperta
    quando civiltà.scopre(PropulsioneAntimaterica) {
        dice: "Antimaterica. Sai cosa significa questo?
               Significa che niente — assolutamente niente — 
               può più fermarvi."
        tono: entusiasta
    }
    
    // Reazione a una risorsa esaurita
    quando risorsa.esaurita(Carbone) e era.corrente == Steampunk {
        dice: "Il carbone finisce. L'era del vapore sta tramontando.
               È tempo di guardare oltre."
        tono: neutro
    }
    
    // Reazione a un tentativo di finale Aurora fallito
    quando giocatore.tenta_finale(Aurora) e non civiltà.ha_tecnologia(PropulsioneAntimaterica) {
        dice: "Non ancora. L'Aurora richiede ancora lavoro.
               Ma ci arriverete — ne sono certo."
        tono: incoraggiante
    }
    
    // Reazione se il giocatore ha un flag segreto
    quando era.corrente == Cyber e civiltà.ha_flag(flag_alleanza_oscura) {
        dice: "Ho tenuto molti segreti per te.
               Questo è l'ultimo."
        tono: misterioso
    }
}
```

---

## Integrazione con Imperium

### Struttura delle Cartelle

```
/mods
  /nome_della_tua_mod
    mod.lex              ← file principale della mod
    /ere                 ← file .lex per le ere custom
    /strutture           ← file .lex per le strutture
    /unità               ← file .lex per le unità
    /tecnologie          ← file .lex per le tecnologie
    /eventi              ← file .lex per gli eventi
    /lore                ← file di testo per la lore dell'Archivista
    /audio               ← file audio custom
    /icone               ← icone custom per risorse e strutture
```

### Il file mod.lex

Ogni mod deve avere un file `mod.lex` nella radice:

```lex
mod NomeDellaMod {
    versione: "1.0.0"
    autore: "Il tuo nome"
    descrizione: "Cosa aggiunge la tua mod"
    compatibilità: "Imperium >= 1.0"
    
    include {
        /ere/mia_era_custom.lex
        /strutture/strutture_custom.lex
        /eventi/eventi_custom.lex
    }
}
```

### Compilare e Testare

Una volta installata la mod nella cartella `/mods`, Imperium la carica automaticamente all'avvio. Gli errori Lex vengono mostrati nella console di debug accessibile con `F12` durante il gioco.

Per validare la sintassi senza avviare il gioco:

```bash
imperium --validate-mod /mods/nome_della_tua_mod
```

---

*Documentazione Lex v0.1 — Imperium Game Engine*
*Questa documentazione è in continua evoluzione insieme al gioco.*
