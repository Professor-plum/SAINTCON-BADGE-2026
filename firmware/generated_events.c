#include "eventbase.h"

const event_t random_events[] = {
    {
        .id = 1,
        .title = "Interstellar Customs Authority",
        .description = "A sleek military vessel cuts across your path, running your transponder through stellar databases. Their message crackles over the comm: 'Merchant vessel, prepare for cargo inspection. We've flagged some irregularities in your manifest.' The customs officers await your response.",
        .option_count = 4,
        .options = {
            {
                .description = "Comply fully",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "The officers nod approvingly and clear you for departure. Your professionalism earns their respect.",
                        .name = "The officers nod approvingly and clear you for departure. Your professionalism earns their respect.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = 10,
                            },
                        },
                    },
                    {
                        .description = "Their scanners find discrepancies in your documentation. Valuable cargo gets impounded.",
                        .name = "Their scanners find discrepancies in your documentation. Valuable cargo gets impounded.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -8,
                            },
                        },
                    },
                },
            },
            {
                .description = "Bribe the officer",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "The bribe works perfectly. The lead officer pockets it discreetly and waves you through.",
                        .name = "The bribe works perfectly. The lead officer pockets it discreetly and waves you through.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -1,
                            },
                        },
                    },
                    {
                        .description = "Internal affairs was monitoring. You're caught red-handed and face severe penalties.",
                        .name = "Internal affairs was monitoring. You're caught red-handed and face severe penalties.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -15,
                            },
                        },
                    },
                },
            },
            {
                .description = "Hide contraband",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your contraband stays hidden. The inspection finds nothing suspicious.",
                        .name = "Your contraband stays hidden. The inspection finds nothing suspicious.",
                        .chance = 70,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "A routine secondary scan exposes your illegal goods. Confiscation is swift and total.",
                        .name = "A routine secondary scan exposes your illegal goods. Confiscation is swift and total.",
                        .chance = 30,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -15,
                            },
                        },
                    },
                },
            },
            {
                .description = "Forge documents (Scientist)",
                .requirements = EV_FLAG_REQUIRES_SCIENTIST,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your scientist's forgery is masterful-flawless enough to survive computer verification.",
                        .name = "Your scientist's forgery is masterful-flawless enough to survive computer verification.",
                        .chance = 80,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The military's cryptographic analysis exposes the fake documents immediately. Legal trouble ensues.",
                        .name = "The military's cryptographic analysis exposes the fake documents immediately. Legal trouble ensues.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -8,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 2,
        .title = "Graveyard of Lost Starships",
        .description = "Your sensors suddenly light up with thousands of contacts. Before you lies a massive debris field-the scattered remains of an ancient space battle. Jagged hull plating and twisted metal drift silently through the void like tombstones. Your navigation computer urges caution as you approach.",
        .option_count = 4,
        .options = {
            {
                .description = "Attempt manual maneuvering",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your pilot navigates the field with surgical precision. The crew gains valuable experience.",
                        .name = "Your pilot navigates the field with surgical precision. The crew gains valuable experience.",
                        .chance = 75,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_XP,
                                .value = 50,
                            },
                        },
                    },
                    {
                        .description = "A hidden piece of debris rips into your starboard hull. The damage is substantial.",
                        .name = "A hidden piece of debris rips into your starboard hull. The damage is substantial.",
                        .chance = 25,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Travel around",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your course adjustment takes you safely around the wreckage.",
                        .name = "Your course adjustment takes you safely around the wreckage.",
                        .chance = 50,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The detour burns precious fuel as you work around the wreckage.",
                        .name = "The detour burns precious fuel as you work around the wreckage.",
                        .chance = 50,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Call for help",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "A nearby pilot group intercepts your call and clears a path. You owe them a favor.",
                        .name = "A nearby pilot group intercepts your call and clears a path. You owe them a favor.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = 10,
                            },
                        },
                    },
                    {
                        .description = "They demand payment for the help in the form of precious cargo.",
                        .name = "They demand payment for the help in the form of precious cargo.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -5,
                            },
                        },
                    },
                },
            },
            {
                .description = "Advanced navigation (Pilot)",
                .requirements = EV_FLAG_REQUIRES_PILOT,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your pilot's expertise cuts through the debris field like a knife. The crew is astounded.",
                        .name = "Your pilot's expertise cuts through the debris field like a knife. The crew is astounded.",
                        .chance = 80,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_XP,
                                .value = 50,
                            },
                        },
                    },
                    {
                        .description = "A grazing impact marks your hull, but mostly you make it through unscathed.",
                        .name = "A grazing impact marks your hull, but mostly you make it through unscathed.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 4,
        .title = "Raiders from the Crimson Nebula",
        .description = "Three ships emerge from the radiation haze of the Crimson Nebula, cutting off your escape vector. A gravelly voice breaks through your comms: 'Stand down, merchant. Your cargo is confiscated. Resist and we'll take the whole ship.' Pirate raiders have found you.",
        .option_count = 4,
        .options = {
            {
                .description = "Fight back",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your crew fights with desperate courage. The pirates flee, leaving their plunder behind.",
                        .name = "Your crew fights with desperate courage. The pirates flee, leaving their plunder behind.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = 20,
                            },
                        },
                    },
                    {
                        .description = "The engagement is fierce. Your hull takes punishing hits before they withdraw.",
                        .name = "The engagement is fierce. Your hull takes punishing hits before they withdraw.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Flee",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your engines roar to life. You punch through the pirate blockade and disappear into hyperspace.",
                        .name = "Your engines roar to life. You punch through the pirate blockade and disappear into hyperspace.",
                        .chance = 70,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "They cut off your escape route. Cargo jettison is your only option to gain speed.",
                        .name = "They cut off your escape route. Cargo jettison is your only option to gain speed.",
                        .chance = 30,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -16,
                            },
                        },
                    },
                },
            },
            {
                .description = "Negotiate",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Cunning words and a small tribute satisfy the raiders. They let you pass.",
                        .name = "Cunning words and a small tribute satisfy the raiders. They let you pass.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -5,
                            },
                        },
                    },
                    {
                        .description = "Their demands escalate. You're forced to surrender more than you offered.",
                        .name = "Their demands escalate. You're forced to surrender more than you offered.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -8,
                            },
                        },
                    },
                },
            },
            {
                .description = "Security response (Security)",
                .requirements = EV_FLAG_REQUIRES_SOLDIER,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your security team repels the attack before it even starts. The pirates retreat in shame.",
                        .name = "Your security team repels the attack before it even starts. The pirates retreat in shame.",
                        .chance = 80,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = 8,
                            },
                        },
                    },
                    {
                        .description = "The brief firefight is over quickly, but your hull bears the scars.",
                        .name = "The brief firefight is over quickly, but your hull bears the scars.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 5,
        .title = "The Obsidian Monolith",
        .description = "Deep in a forgotten asteroid field, your salvage scanner detects something: a perfectly geometric obsidian structure, pulsing with an unidentifiable energy signature. Whatever this ancient artifact is, it seems to predate any known civilization. Its origins-and purpose-remain a complete mystery.",
        .option_count = 4,
        .options = {
            {
                .description = "Sell it",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "A collectors' market hungers for alien relics. You pocket a tidy sum.",
                        .name = "A collectors' market hungers for alien relics. You pocket a tidy sum.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = 80,
                            },
                        },
                    },
                    {
                        .description = "You sell it cheaply, realizing too late it was far more valuable intact.",
                        .name = "You sell it cheaply, realizing too late it was far more valuable intact.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_XP,
                                .value = -10,
                            },
                        },
                    },
                },
            },
            {
                .description = "Keep it",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "The artifact remains yours. You sense it will bring unforeseen advantages later.",
                        .name = "The artifact remains yours. You sense it will bring unforeseen advantages later.",
                        .chance = 70,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = 80,
                            },
                        },
                    },
                    {
                        .description = "The monolith takes up valuable space. Your cargo capacity is severely limited.",
                        .name = "The monolith takes up valuable space. Your cargo capacity is severely limited.",
                        .chance = 30,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Ignore it",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Leaving it behind feels safe, and you continue on your way without incident.",
                        .name = "Leaving it behind feels safe, and you continue on your way without incident.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Later reports suggest the artifact held technology worth fortunes. You missed it.",
                        .name = "Later reports suggest the artifact held technology worth fortunes. You missed it.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Study it (Scientist)",
                .requirements = EV_FLAG_REQUIRES_SCIENTIST,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your scientist's analysis reveals a way to harness its power safely. A breakthrough!",
                        .name = "Your scientist's analysis reveals a way to harness its power safely. A breakthrough!",
                        .chance = 80,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "As they study it, the artifact destabilizes violently. Energy floods the hold.",
                        .name = "As they study it, the artifact destabilizes violently. Energy floods the hold.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 6,
        .title = "The Dying Freighter",
        .description = "A distress beacon pulls your attention toward a crippled deep-space freighter, its reactor stuttering dangerously. Through the viewscreen, you see a damaged hull and desperate crew signals. The captain's voice comes through, barely a whisper: 'Please... we're running on fumes. Can anyone help?'",
        .option_count = 3,
        .options = {
            {
                .description = "Sell them 3 fuel",
                .requirements = EV_FLAG_REQUIRES_FUEL,
                .required_count = 3,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "A solid deal. You trade 3 units of fuel for 15 credits. Both sides profit.",
                        .name = "A solid deal. You trade 3 units of fuel for 15 credits. Both sides profit.",
                        .chance = 60,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -3,
                            },
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = 15,
                            },
                        },
                    },
                    {
                        .description = "They're so desperate they offer 30 credits. Easy money.",
                        .name = "They're so desperate they offer 30 credits. Easy money.",
                        .chance = 40,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -3,
                            },
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = 30,
                            },
                        },
                    },
                },
            },
            {
                .description = "Give them 5 Fuel",
                .requirements = EV_FLAG_REQUIRES_FUEL,
                .required_count = 3,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Grateful and relieved, they load your hold with salvage and rare materials.",
                        .name = "Grateful and relieved, they load your hold with salvage and rare materials.",
                        .chance = 70,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -3,
                            },
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = 10,
                            },
                        },
                    },
                    {
                        .description = "They're grateful for your mercy, but can only offer thanks and well-wishes.",
                        .name = "They're grateful for your mercy, but can only offer thanks and well-wishes.",
                        .chance = 30,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -3,
                            },
                            {
                                .type = EV_EFFECT_XP,
                                .value = 20,
                            },
                        },
                    },
                },
            },
            {
                .description = "Leave them, you can't spare the fuel",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You accelerate away, but they make no hostile move. Just desperate silence.",
                        .name = "You accelerate away, but they make no hostile move. Just desperate silence.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "As you jump to hyperspace, they fire on you in desperation. You're struck hard.",
                        .name = "As you jump to hyperspace, they fire on you in desperation. You're struck hard.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 7,
        .title = "Mutiny Brewing Below Decks",
        .description = "Tension explodes between your crew members in the commons bay. Your navigator and cargo master are locked in heated debate about mission priorities. Voices rise. Fists clench. If you don't intervene soon, this could tear the crew apart.",
        .option_count = 4,
        .options = {
            {
                .description = "Mediate",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your calm mediation brings the crew to compromise. Unity restored and morale boosted.",
                        .name = "Your calm mediation brings the crew to compromise. Unity restored and morale boosted.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_XP,
                                .value = 20,
                            },
                        },
                    },
                    {
                        .description = "The debate drags on, but eventually tempers cool and the crew reaches compromise.",
                        .name = "The debate drags on, but eventually tempers cool and the crew reaches compromise.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Ignore",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You maintain course. The argument fades as priorities shift. Nothing breaks.",
                        .name = "You maintain course. The argument fades as priorities shift. Nothing breaks.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The dispute festers. Resentment spreads through the crew like poison.",
                        .name = "The dispute festers. Resentment spreads through the crew like poison.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_XP,
                                .value = -20,
                            },
                        },
                    },
                },
            },
            {
                .description = "Pick a side",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "One side feels vindicated. The issue is settled, though some harbor quiet resentment.",
                        .name = "One side feels vindicated. The issue is settled, though some harbor quiet resentment.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Those on the losing side feel slighted. Friction remains below the surface.",
                        .name = "Those on the losing side feel slighted. Friction remains below the surface.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_XP,
                                .value = -20,
                            },
                        },
                    },
                },
            },
            {
                .description = "Counsel crew (Medic)",
                .requirements = EV_FLAG_REQUIRES_MEDIC,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your medic's counseling brings clarity. The crew's spirits soar with newfound purpose.",
                        .name = "Your medic's counseling brings clarity. The crew's spirits soar with newfound purpose.",
                        .chance = 70,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_XP,
                                .value = 20,
                            },
                        },
                    },
                    {
                        .description = "The session is intense and ultimately strengthens the crew's unity.",
                        .name = "The session is intense and ultimately strengthens the crew's unity.",
                        .chance = 30,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
        },
    },
    {
        .id = 8,
        .title = "Bio-Hazard Alert",
        .description = "A routine scan triggers your ship's alarm system. Biohazard readings spike in the cargo bay-something in one of your containers has become contaminated with an unknown pathogen. The cargo holds 80% of your profits for this run. What do you do?",
        .option_count = 4,
        .options = {
            {
                .description = "Dispose of it",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You make the hard call. The contaminated cargo is spaced. Risk averted.",
                        .name = "You make the hard call. The contaminated cargo is spaced. Risk averted.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -2,
                            },
                        },
                    },
                    {
                        .description = "Attempting disposal causes a catastrophic vent. Most of your cargo is lost in the process.",
                        .name = "Attempting disposal causes a catastrophic vent. Most of your cargo is lost in the process.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -16,
                            },
                        },
                    },
                },
            },
            {
                .description = "Sell it anyway",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You sell it anyway. The buyers never notice the contamination. Profit secured.",
                        .name = "You sell it anyway. The buyers never notice the contamination. Profit secured.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Word spreads. Your reputation for cutting corners is now known across the sector.",
                        .name = "Word spreads. Your reputation for cutting corners is now known across the sector.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = -10,
                            },
                        },
                    },
                },
            },
            {
                .description = "Quarantine it",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Isolation and careful handling preserve most of your cargo. A smart call pays off.",
                        .name = "Isolation and careful handling preserve most of your cargo. A smart call pays off.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -6,
                            },
                        },
                    },
                    {
                        .description = "Quarantine procedures are difficult but ultimately effective.",
                        .name = "Quarantine procedures are difficult but ultimately effective.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Analyze contamination (Scientist)",
                .requirements = EV_FLAG_REQUIRES_SCIENTIST,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your scientist neutralizes the pathogen completely. The cargo is salvaged and safe.",
                        .name = "Your scientist neutralizes the pathogen completely. The cargo is salvaged and safe.",
                        .chance = 70,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The analysis shows severe corruption. A portions must still be destroyed.",
                        .name = "The analysis shows severe corruption. A portions must still be destroyed.",
                        .chance = 30,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -8,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 9,
        .title = "Solar Fury Descends",
        .description = "The peaceful starfield erupts in chaos. A massive coronal mass ejection tears from the sun, invisible waves of radiation and charged particles racing toward your vessel. Your alarms wail as the solar storm engulfs your trajectory. Only your quick thinking can save the ship now.",
        .option_count = 4,
        .options = {
            {
                .description = "Wait it out",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You hold your breath and wait. The storm passes harmlessly around you.",
                        .name = "You hold your breath and wait. The storm passes harmlessly around you.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Patience pays off, but your route options narrow.",
                        .name = "Patience pays off, but your route options narrow.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Push through",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your engines burn bright as you punch through. Speed overcomes the radiation waves.",
                        .name = "Your engines burn bright as you punch through. Speed overcomes the radiation waves.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "You made the wrong call. The solar wind batters your hull with violent fury.",
                        .name = "You made the wrong call. The solar wind batters your hull with violent fury.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Secure cargo",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You carefully redistribute weight and secure everything. The cargo holds steady through the storm.",
                        .name = "You carefully redistribute weight and secure everything. The cargo holds steady through the storm.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -1,
                            },
                        },
                    },
                    {
                        .description = "Despite your efforts, the ship pitches violently. Progress slows to a crawl.",
                        .name = "Despite your efforts, the ship pitches violently. Progress slows to a crawl.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Stabilize systems (Engineer)",
                .requirements = EV_FLAG_REQUIRES_ENGINEER,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your engineer makes surgical adjustments to the shield generators. You ride out the storm unscathed.",
                        .name = "Your engineer makes surgical adjustments to the shield generators. You ride out the storm unscathed.",
                        .chance = 80,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The systems strain under the assault. They hold, barely, but not without stress.",
                        .name = "The systems strain under the assault. They hold, barely, but not without stress.",
                        .chance = 20,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
        },
    },
    {
        .id = 10,
        .title = "Dysentery Outbreak",
        .description = "As you ford a treacherous asteroid field, contaminated water from a cracked recycler spreads through the crew. Symptoms of dysentery begin to manifest-fever, dehydration, and weakness. The old trail disease has found its way to the stars.",
        .option_count = 3,
        .options = {
            {
                .description = "Rest and recover",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Most crew recover with rest, but one succumbs to the relentless dysentery.",
                        .name = "Most crew recover with rest, but one succumbs to the relentless dysentery.",
                        .chance = 70,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                    {
                        .description = "The outbreak worsens during rest. Multiple crew members are lost to the illness.",
                        .name = "The outbreak worsens during rest. Multiple crew members are lost to the illness.",
                        .chance = 30,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Push through",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You continue despite the illness. One crew member collapses and doesn't recover.",
                        .name = "You continue despite the illness. One crew member collapses and doesn't recover.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                    {
                        .description = "The strain proves fatal. Dysentery claims two lives before you can stop it.",
                        .name = "The strain proves fatal. Dysentery claims two lives before you can stop it.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Treat with medicine (Medic)",
                .requirements = EV_FLAG_REQUIRES_MEDIC,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your medic administers effective treatment. The outbreak is contained with minimal loss.",
                        .name = "Your medic administers effective treatment. The outbreak is contained with minimal loss.",
                        .chance = 80,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Treatment helps, but one crew member still falls to the disease.",
                        .name = "Treatment helps, but one crew member still falls to the disease.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 13,
        .title = "The Crystalline Trader",
        .description = "A vessel of impossible geometry shimmers into view-a ship that shouldn't be able to exist within normal spacetime. Its pilot, a being of pulsing crystalline light, makes contact: 'I have goods no other civilization possesses. Interested in trade... friend?'",
        .option_count = 3,
        .options = {
            {
                .description = "Accept trade",
                .requirements = EV_FLAG_REQUIRES_CARGO,
                .required_count = 8,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "The crystal being smiles-if such a thing is possible. The trade brings mutual benefit and profit.",
                        .name = "The crystal being smiles-if such a thing is possible. The trade brings mutual benefit and profit.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The deal seems legitimate. Your instincts say something is off, but you accept anyway.",
                        .name = "The deal seems legitimate. Your instincts say something is off, but you accept anyway.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Decline",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You politely refuse. No complications or entanglements follow.",
                        .name = "You politely refuse. No complications or entanglements follow.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "You decline, but the offer haunts you. What if you'd taken it?",
                        .name = "You decline, but the offer haunts you. What if you'd taken it?",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Negotiate",
                .requirements = EV_FLAG_REQUIRES_CARGO,
                .required_count = 8,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your counteroffers are sharp. The merchant relents and gives you an even better price.",
                        .name = "Your counteroffers are sharp. The merchant relents and gives you an even better price.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "They refuse to budge further. You take their original offer or walk away empty-handed.",
                        .name = "They refuse to budge further. You take their original offer or walk away empty-handed.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
        },
    },
    {
        .id = 14,
        .title = "The Faulty Star Charts",
        .description = "Your navigation console flickers with a warning. The maps you're using-supposedly updated just weeks ago-contain significant errors. A critical waypoint listed on your charts doesn't exist. Other routes suddenly lead nowhere. Your trajectory is compromised.",
        .option_count = 3,
        .options = {
            {
                .description = "Proceed anyway",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Luck favors the bold. You navigate the corrected course and save significant effort.",
                        .name = "Luck favors the bold. You navigate the corrected course and save significant effort.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The maps lead you astray. You waste precious fuel correcting your course.",
                        .name = "The maps lead you astray. You waste precious fuel correcting your course.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Recalculate",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your careful recalculations yield a safe, indirect route that ensures accuracy.",
                        .name = "Your careful recalculations yield a safe, indirect route that ensures accuracy.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The detour is costly, but you're confident in the path now.",
                        .name = "The detour is costly, but you're confident in the path now.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Pilot correction (Pilot)",
                .requirements = EV_FLAG_REQUIRES_PILOT,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your pilot's instincts are flawless. They chart a shortcut that saves fuel and resources alike.",
                        .name = "Your pilot's instincts are flawless. They chart a shortcut that saves fuel and resources alike.",
                        .chance = 80,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Even with the pilot's skill, stellar drift causes minor course corrections and fuel burn.",
                        .name = "Even with the pilot's skill, stellar drift causes minor course corrections and fuel burn.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 16,
        .title = "Shadows in the Docking Bay",
        .description = "A hooded figure approaches you in the darkened docking bay, glancing over their shoulder nervously. 'I know what you carry. I know what you want to carry. I can get you goods-valuable, illegal, off-the-books goods. No questions asked. Interested?' The offer hangs dangerous and tantalizing.",
        .option_count = 3,
        .options = {
            {
                .description = "Buy",
                .requirements = EV_FLAG_REQUIRES_CREDITS,
                .required_count = 50,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "The illegal goods are legitimate treasure. Your hold suddenly becomes far more valuable.",
                        .name = "The illegal goods are legitimate treasure. Your hold suddenly becomes far more valuable.",
                        .chance = 60,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = -50,
                            },
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = 10,
                            },
                        },
                    },
                    {
                        .description = "The goods turn out to be low-quality forgeries. You wasted money on garbage.",
                        .name = "The goods turn out to be low-quality forgeries. You wasted money on garbage.",
                        .chance = 40,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = -50,
                            },
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = 5,
                            },
                        },
                    },
                },
            },
            {
                .description = "Ignore",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 1,
                .outcomes = {
                    {
                        .description = "Wisdom prevails. You pass on the deal and sleep well that night.",
                        .name = "Wisdom prevails. You pass on the deal and sleep well that night.",
                        .chance = 100,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Report",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Reporting the smuggler earns you a tidy bounty from the authorities.",
                        .name = "Reporting the smuggler earns you a tidy bounty from the authorities.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = 50,
                            },
                        },
                    },
                    {
                        .description = "The bureaucratic process drags on. Your schedule crumbles.",
                        .name = "The bureaucratic process drags on. Your schedule crumbles.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
        },
    },
    {
        .id = 17,
        .title = "The Orphaned Probe",
        .description = "Drifting lazily across your scanner is an abandoned drone, its transponder still weakly broadcasting. It's heavily damaged but-if you had to guess-still functional. Someone lost this out here. The question is: who, and is it worth recovering?",
        .option_count = 3,
        .options = {
            {
                .description = "Recover it",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your salvage scanner identifies valuable components. This find is worth credits and cargo space.",
                        .name = "Your salvage scanner identifies valuable components. This find is worth credits and cargo space.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = 2,
                            },
                        },
                    },
                    {
                        .description = "It looks valuable but turns out to be corroded scrap. A waste of effort.",
                        .name = "It looks valuable but turns out to be corroded scrap. A waste of effort.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Ignore",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 1,
                .outcomes = {
                    {
                        .description = "You leave it behind without second thought. Peace prevails.",
                        .name = "You leave it behind without second thought. Peace prevails.",
                        .chance = 100,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Repair it (Engineer)",
                .requirements = EV_FLAG_REQUIRES_ENGINEER,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "The drone's owner makes contact via hidden systems. A generous reward is transferred immediately.",
                        .name = "The drone's owner makes contact via hidden systems. A generous reward is transferred immediately.",
                        .chance = 50,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = 50,
                            },
                        },
                    },
                    {
                        .description = "The drone is an advanced repair unit. Upon activation, it strengthens your hull integrity.",
                        .name = "The drone is an advanced repair unit. Upon activation, it strengthens your hull integrity.",
                        .chance = 50,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = 1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 18,
        .title = "The Glowing Plague",
        .description = "Geiger counters erupt in a cacophony of clicks and whines. Your cargo bay is bathed in hazardous radiation-something in your shipment has broken containment. The crew runs for protective gear while your systems sound increasingly frantic warnings. Time is not your friend here.",
        .option_count = 4,
        .options = {
            {
                .description = "Vent bay",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You blow the airlock. Radiation vents into space and the threat vanishes.",
                        .name = "You blow the airlock. Radiation vents into space and the threat vanishes.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -3,
                            },
                        },
                    },
                    {
                        .description = "The vent process is slow and complicated. Radiation lingers longer than expected.",
                        .name = "The vent process is slow and complicated. Radiation lingers longer than expected.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -5,
                            },
                        },
                    },
                },
            },
            {
                .description = "Seal it",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You seal the bay tight. The radiation is contained, though it lingers behind closed doors.",
                        .name = "You seal the bay tight. The radiation is contained, though it lingers behind closed doors.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -3,
                            },
                        },
                    },
                    {
                        .description = "The seal holds... for now. But stored energy could rupture it anytime.",
                        .name = "The seal holds... for now. But stored energy could rupture it anytime.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -4,
                            },
                        },
                    },
                },
            },
            {
                .description = "Ignore",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "The radiation dissipates naturally. No further incident occurs.",
                        .name = "The radiation dissipates naturally. No further incident occurs.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Crew members begin showing radiation sickness. One falls critically ill.",
                        .name = "Crew members begin showing radiation sickness. One falls critically ill.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Treat exposure (Medic)",
                .requirements = EV_FLAG_REQUIRES_MEDIC,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your medic administers preventative treatment. The crew recovers without lasting harm.",
                        .name = "Your medic administers preventative treatment. The crew recovers without lasting harm.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The treatment process is difficult and only partially succeeds. No casualties, but the crew is weakened.",
                        .name = "The treatment process is difficult and only partially succeeds. No casualties, but the crew is weakened.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
        },
    },
    {
        .id = 19,
        .title = "When Systems Fail",
        .description = "A shower of sparks erupts from the engine compartment. Your second engineer limps out, blackened and shaken. 'Captain, we've got a critical failure in the main turbine assembly. It's holding for now, barely, but if it gives way completely...'",
        .option_count = 4,
        .options = {
            {
                .description = "Repair",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your engineers work through the night. By dawn, the component is fully restored.",
                        .name = "Your engineers work through the night. By dawn, the component is fully restored.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Repairs take longer than anticipated. Progress stalls while you work.",
                        .name = "Repairs take longer than anticipated. Progress stalls while you work.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Replace",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "The replacement part installs perfectly and performs better than the original.",
                        .name = "The replacement part installs perfectly and performs better than the original.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The new component is expensive. Your emergency credits take a hit.",
                        .name = "The new component is expensive. Your emergency credits take a hit.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = -50,
                            },
                        },
                    },
                },
            },
            {
                .description = "Ignore",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "The component holds for now. You maintain speed and pressure as if nothing is wrong.",
                        .name = "The component holds for now. You maintain speed and pressure as if nothing is wrong.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The failure is postponed, not prevented. Viloent vibrations and power fluctuations plague your systems.",
                        .name = "The failure is postponed, not prevented. Viloent vibrations and power fluctuations plague your systems.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -3,
                            },
                        },
                    },
                },
            },
            {
                .description = "Optimize fix (Engineer)",
                .requirements = EV_FLAG_REQUIRES_ENGINEER,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your engineer tweaks the repairs to achieve better-than-new performance. ",
                        .name = "Your engineer tweaks the repairs to achieve better-than-new performance. ",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = 1,
                            },
                        },
                    },
                    {
                        .description = "The optimization process is complex. Some gains are realized, but not all.",
                        .name = "The optimization process is complex. Some gains are realized, but not all.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
        },
    },
    {
        .id = 20,
        .title = "Plague Among Your People",
        .description = "Your best navigator collapses on the bridge. Fever. Chills. An illness spreading through your ranks with disturbing speed. The medical officer looks grim: 'Captain, I've never seen anything like this before. Whatever this is, it could incapacitate the crew.'",
        .option_count = 3,
        .options = {
            {
                .description = "Rest",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Rest works wonders. Your crew member returns to full duty.",
                        .name = "Rest works wonders. Your crew member returns to full duty.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Recovery is slower than hoped. You're forced to maintain reduced operational tempo.",
                        .name = "Recovery is slower than hoped. You're forced to maintain reduced operational tempo.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Push on",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your crew member pushes through. They're determined to keep working despite the illness.",
                        .name = "Your crew member pushes through. They're determined to keep working despite the illness.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The illness worsens dramatically. Your crew member becomes bedridden and useless.",
                        .name = "The illness worsens dramatically. Your crew member becomes bedridden and useless.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Treat illness (Medic)",
                .requirements = EV_FLAG_REQUIRES_MEDIC,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your medic prescribes the perfect treatment. Recovery is swift and complete.",
                        .name = "Your medic prescribes the perfect treatment. Recovery is swift and complete.",
                        .chance = 80,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The treatment helps, but the recovery process still demands careful observation.",
                        .name = "The treatment helps, but the recovery process still demands careful observation.",
                        .chance = 20,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
        },
    },
    {
        .id = 21,
        .title = "Fortune in the Deep",
        .description = "While exploring a dead moon's caverns, your survey team falls through a concealed floor into an ancient vault. Cases upon cases of pristine, pre-war goods sit untouched for centuries. Whoever hid this treasure left no explanation-just riches waiting in the darkness.",
        .option_count = 4,
        .options = {
            {
                .description = "Take all",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your team loads everything. Riches beyond measure now fill your hold.",
                        .name = "Your team loads everything. Riches beyond measure now fill your hold.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = 10,
                            },
                        },
                    },
                    {
                        .description = "The vault collapses as you grab the last case. The concussion damages your ship.",
                        .name = "The vault collapses as you grab the last case. The concussion damages your ship.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Take some",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You fill several crates with the most valuable items and depart cautiously.",
                        .name = "You fill several crates with the most valuable items and depart cautiously.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = 5,
                            },
                        },
                    },
                    {
                        .description = "You could have carried more if you'd been bolder. Hindsight is cruel.",
                        .name = "You could have carried more if you'd been bolder. Hindsight is cruel.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = 2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Leave it",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You walk away unharmed. Caution was the right call this time.",
                        .name = "You walk away unharmed. Caution was the right call this time.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "You leave empty-handed, wondering what fortune you just passed by.",
                        .name = "You leave empty-handed, wondering what fortune you just passed by.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Scan first (Scientist)",
                .requirements = EV_FLAG_REQUIRES_SCIENTIST,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "The scan reveals no booby traps or dangers. You collect everything safely.",
                        .name = "The scan reveals no booby traps or dangers. You collect everything safely.",
                        .chance = 80,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = 10,
                            },
                        },
                    },
                    {
                        .description = "The scan detects some hazards, but not all. You proceed with caution and partial success.",
                        .name = "The scan detects some hazards, but not all. You proceed with caution and partial success.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = 5,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 22,
        .title = "Giant Spider Infestation",
        .description = "Boarding a derelict freighter for salvage, your team discovers a nightmare: massive, genetically engineered spiders that have overrun the ship. Their webs clog corridors, and their venomous bites threaten your crew.",
        .option_count = 3,
        .options = {
            {
                .description = "Fight them off",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your crew battles fiercely and clears the spiders, but one member falls to venomous bites.",
                        .name = "Your crew battles fiercely and clears the spiders, but one member falls to venomous bites.",
                        .chance = 70,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = 5,
                            },
                        },
                    },
                    {
                        .description = "The spiders overwhelm your team. Multiple crew are lost in the arachnid assault.",
                        .name = "The spiders overwhelm your team. Multiple crew are lost in the arachnid assault.",
                        .chance = 30,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Seal and abandon",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 1,
                .outcomes = {
                    {
                        .description = "You seal the derelict and retreat safely, losing the salvage opportunity.",
                        .name = "You seal the derelict and retreat safely, losing the salvage opportunity.",
                        .chance = 100,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Capture specimens (Scientist)",
                .requirements = EV_FLAG_REQUIRES_SCIENTIST,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your scientist captures live specimens for study, yielding valuable research data.",
                        .name = "Your scientist captures live specimens for study, yielding valuable research data.",
                        .chance = 80,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = 60,
                            },
                            {
                                .type = EV_EFFECT_XP,
                                .value = 20,
                            },
                        },
                    },
                    {
                        .description = "During capture, a spider escapes and bites a crew member fatally.",
                        .name = "During capture, a spider escapes and bites a crew member fatally.",
                        .chance = 20,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = 50,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 23,
        .title = "Silence Across the Void",
        .description = "Your communication systems dissolve into white noise and static. Every channel screams with interference from an unknown source. You're cut off from the wider galaxy-blind and unable to reach help or contact anyone out there. Just you and the void.",
        .option_count = 4,
        .options = {
            {
                .description = "Wait",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You hold position and wait patiently. The interference clears as mysteriously as it came.",
                        .name = "You hold position and wait patiently. The interference clears as mysteriously as it came.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Silence stretches on, but eventually the interference subsides.",
                        .name = "Silence stretches on, but eventually the interference subsides.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Boost signal",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Power surges through your communications array. The distortion breaks and clarity returns.",
                        .name = "Power surges through your communications array. The distortion breaks and clarity returns.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The boost succeeds but drains your power reserves faster than expected.",
                        .name = "The boost succeeds but drains your power reserves faster than expected.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Ignore",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You proceed without communications. It's risky, but you maintain course.",
                        .name = "You proceed without communications. It's risky, but you maintain course.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Critical information passes you by. You miss important signals and opportunities.",
                        .name = "Critical information passes you by. You miss important signals and opportunities.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Calibrate (Engineer)",
                .requirements = EV_FLAG_REQUIRES_ENGINEER,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your engineer's calibration work is flawless. Communications scream through clearly, revealing a hidden cache location.",
                        .name = "Your engineer's calibration work is flawless. Communications scream through clearly, revealing a hidden cache location.",
                        .chance = 80,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = 4,
                            },
                        },
                    },
                    {
                        .description = "The calibration improves things marginally, but requires careful engineering attention.",
                        .name = "The calibration improves things marginally, but requires careful engineering attention.",
                        .chance = 20,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
        },
    },
    {
        .id = 25,
        .title = "Relics of the First Builders",
        .description = "Planetary sensors reveal something extraordinary: monumental structures beneath the world's crust. Architecture that predates any known species, with purpose and scale that makes your crew catch their breath. Could this be the legendary home of the First Builders? A discovery that could rewrite history itself.",
        .option_count = 4,
        .options = {
            {
                .description = "Explore",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your team discovers an underground chamber filled with priceless First Builder artifacts and technology.",
                        .name = "Your team discovers an underground chamber filled with priceless First Builder artifacts and technology.",
                        .chance = 50,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = 60,
                            },
                        },
                    },
                    {
                        .description = "Exploration triggers ancient defense systems. Structures collapse around you.",
                        .name = "Exploration triggers ancient defense systems. Structures collapse around you.",
                        .chance = 50,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -3,
                            },
                        },
                    },
                },
            },
            {
                .description = "Mark location",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You chart the coordinates precisely. Future expeditions will thank you for this discovery.",
                        .name = "You chart the coordinates precisely. Future expeditions will thank you for this discovery.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = 10,
                            },
                        },
                    },
                    {
                        .description = "You mark it but lack detailed data. Your future notes will be frustratingly vague.",
                        .name = "You mark it but lack detailed data. Your future notes will be frustratingly vague.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Ignore",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Stay safe.",
                        .name = "Stay safe.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Miss opportunity.",
                        .name = "Miss opportunity.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Analyze ruins (Scientist)",
                .requirements = EV_FLAG_REQUIRES_SCIENTIST,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your scientist cracks the ancient code. A blueprint for advanced technology is revealed.",
                        .name = "Your scientist cracks the ancient code. A blueprint for advanced technology is revealed.",
                        .chance = 80,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The analysis triggers dormant security protocols. Ancient weapons activate.",
                        .name = "The analysis triggers dormant security protocols. Ancient weapons activate.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 26,
        .title = "Too Much, Too Heavy",
        .description = "Red warnings blare across every console: CARGO BAY OVERSTRESSED. Structural beams groan under dangerous weight. Engineers exchange worried glances: 'Captain, if we take any more stress, the bay could rupture. We need to act now.'",
        .option_count = 4,
        .options = {
            {
                .description = "Dump excess cargo",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You jettison the least valuable goods. The bay restabilizes without incident.",
                        .name = "You jettison the least valuable goods. The bay restabilizes without incident.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -5,
                            },
                        },
                    },
                    {
                        .description = "You dump too much too fast. The loss is more severe than projected.",
                        .name = "You dump too much too fast. The loss is more severe than projected.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -10,
                            },
                        },
                    },
                },
            },
            {
                .description = "Reorganize load",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your crew redistributes weight with surgical precision. The cargo bay achieves stable equilibrium.",
                        .name = "Your crew redistributes weight with surgical precision. The cargo bay achieves stable equilibrium.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The physical reorganization is exhausting. Your crew burns energy on tedious rearrangement.",
                        .name = "The physical reorganization is exhausting. Your crew burns energy on tedious rearrangement.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Ignore warnings",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You push forward at full speed. The overloaded bay holds-barely.",
                        .name = "You push forward at full speed. The overloaded bay holds-barely.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Something has to give. Structural supports fail spectacularly.",
                        .name = "Something has to give. Structural supports fail spectacularly.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Optimize load (Engineer)",
                .requirements = EV_FLAG_REQUIRES_ENGINEER,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your engineer uses advanced techniques to pack everything weightlessly. Maximum cargo, zero risk.",
                        .name = "Your engineer uses advanced techniques to pack everything weightlessly. Maximum cargo, zero risk.",
                        .chance = 80,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Some optimization is achieved, but not the deep improvement you hoped for.",
                        .name = "Some optimization is achieved, but not the deep improvement you hoped for.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -3,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 27,
        .title = "An Unexpected Passenger",
        .description = "Your security team drags out a frightened figure from the cargo hold-someone's been hiding in your ship, probably for days. Where did they come from? What do they want? And most importantly... are they a threat to you and your crew?",
        .option_count = 4,
        .options = {
            {
                .description = "Interrogate them",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "The stowaway reveals valuable intelligence about smuggling routes and black market operations.",
                        .name = "The stowaway reveals valuable intelligence about smuggling routes and black market operations.",
                        .chance = 60,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = 20,
                            },
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = 10,
                            },
                        },
                    },
                    {
                        .description = "They become defensive and hostile. Tensions spike as your crew puts them in the brig.",
                        .name = "They become defensive and hostile. Tensions spike as your crew puts them in the brig.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Eject them",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You flush them out the airlock without ceremony. The risk is gone.",
                        .name = "You flush them out the airlock without ceremony. The risk is gone.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = -10,
                            },
                        },
                    },
                    {
                        .description = "As they eject, you realize they might have been useful... or valuable to someone.",
                        .name = "As they eject, you realize they might have been useful... or valuable to someone.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = -5,
                            },
                        },
                    },
                },
            },
            {
                .description = "Let them stay",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You grant them sanctuary. Days later, they prove invaluable during a crisis.",
                        .name = "You grant them sanctuary. Days later, they prove invaluable during a crisis.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = 1,
                            },
                        },
                    },
                    {
                        .description = "They appear grateful, then vanish with crucial data and expensive supplies. Betrayal.",
                        .name = "They appear grateful, then vanish with crucial data and expensive supplies. Betrayal.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Assess threat (Security)",
                .requirements = EV_FLAG_REQUIRES_SOLDIER,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your security team reads the stowaway correctly. You make the best decision for your ship.",
                        .name = "Your security team reads the stowaway correctly. You make the best decision for your ship.",
                        .chance = 80,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = 10,
                            },
                        },
                    },
                    {
                        .description = "Your team misreads the situation. You take the wrong action, and it costs you.",
                        .name = "Your team misreads the situation. You take the wrong action, and it costs you.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 29,
        .title = "Bleeding Through Space",
        .description = "Your fuel indicator twitches downward with alarming speed. The engineers report catastrophic news: a rupture in the starboard fuel line. Your precious reserves are leaking into the void, leaving a trail of antimatter vapor that glows like a beacon to anyone hunting you.",
        .option_count = 4,
        .options = {
            {
                .description = "Seal leak",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your engineers rapidly patch the rupture. Fuel loss is minimal and controlled.",
                        .name = "Your engineers rapidly patch the rupture. Fuel loss is minimal and controlled.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -1,
                            },
                        },
                    },
                    {
                        .description = "The patch holds, but the repair process is more demanding than you'd like.",
                        .name = "The patch holds, but the repair process is more demanding than you'd like.",
                        .chance = 40,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -1,
                            },
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Ignore temporarily",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You maintain course and pressure. The leak remains manageable for the short term.",
                        .name = "You maintain course and pressure. The leak remains manageable for the short term.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -2,
                            },
                        },
                    },
                    {
                        .description = "The leak becomes critical. A fuel ignition reaction erupts through the ship.",
                        .name = "The leak becomes critical. A fuel ignition reaction erupts through the ship.",
                        .chance = 40,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Dump fuel",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You vent all compromised fuel reserves. The hazard is completely neutralized.",
                        .name = "You vent all compromised fuel reserves. The hazard is completely neutralized.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -4,
                            },
                        },
                    },
                    {
                        .description = "You dump more fuel than necessary. The waste is catastrophic to your reserves.",
                        .name = "You dump more fuel than necessary. The waste is catastrophic to your reserves.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -5,
                            },
                        },
                    },
                },
            },
            {
                .description = "Patch system (Engineer)",
                .requirements = EV_FLAG_REQUIRES_ENGINEER,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your engineer applies a brilliant solution. Fuel loss is reduced to minimal amounts.",
                        .name = "Your engineer applies a brilliant solution. Fuel loss is reduced to minimal amounts.",
                        .chance = 80,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = 0,
                            },
                        },
                    },
                    {
                        .description = "The patch works but isn't perfect. Some additional fuel still leaks away.",
                        .name = "The patch works but isn't perfect. Some additional fuel still leaks away.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 35,
        .title = "The Calling",
        .description = "Your comms array picks up an eerie pulse-a signal so elegant, so perfectly structured, that it can't possibly be natural. It repeats in a measured cadence, almost like morse code, but in no language your translators recognize. It pulls at your curiosity like nothing you've felt before.",
        .option_count = 4,
        .options = {
            {
                .description = "Investigate",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You trace the signal to an advanced alien probe containing unprecedented scientific data. Knowledge and reputation surge.",
                        .name = "You trace the signal to an advanced alien probe containing unprecedented scientific data. Knowledge and reputation surge.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = 10,
                            },
                        },
                    },
                    {
                        .description = "The signal was a lure. Armed satellites activate and begin targeting you.",
                        .name = "The signal was a lure. Armed satellites activate and begin targeting you.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Ignore",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You dismiss the signal and continue unimpeded. Safety prevails over curiosity.",
                        .name = "You dismiss the signal and continue unimpeded. Safety prevails over curiosity.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Later, you learn the signal contained investment opportunities worth millions. You missed them.",
                        .name = "Later, you learn the signal contained investment opportunities worth millions. You missed them.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = -10,
                            },
                        },
                    },
                },
            },
            {
                .description = "Record it",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You capture the signal perfectly. The signal contained great investment opportunities",
                        .name = "You capture the signal perfectly. The signal contained great investment opportunities",
                        .chance = 60,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = 5,
                            },
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = 50,
                            },
                        },
                    },
                    {
                        .description = "The recording is corrupted with noise and interference. Analysis yields nothing useful.",
                        .name = "The recording is corrupted with noise and interference. Analysis yields nothing useful.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Decode (Scientist)",
                .requirements = EV_FLAG_REQUIRES_SCIENTIST,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your scientist cracks the encrypted message. It reveals coordinates to an uncharted wealth cache.",
                        .name = "Your scientist cracks the encrypted message. It reveals coordinates to an uncharted wealth cache.",
                        .chance = 80,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = 5,
                            },
                        },
                    },
                    {
                        .description = "As your scientist decodes it, the signal overloads your equipment. Systems blow violently.",
                        .name = "As your scientist decodes it, the signal overloads your equipment. Systems blow violently.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 36,
        .title = "Phantom Thieves",
        .description = "Inventory doesn't match. Valuable cargo has simply vanished from a locked hold with no sign of tampering. No alarms triggered. No security footage shows anything. It's as if someone walked through walls. Your crew is on edge. The black market, perhaps? Or something worse?",
        .option_count = 4,
        .options = {
            {
                .description = "Search ship",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your team finds the stolen goods hidden in a smuggler's compartment. Recovery complete.",
                        .name = "Your team finds the stolen goods hidden in a smuggler's compartment. Recovery complete.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = 5,
                            },
                        },
                    },
                    {
                        .description = "The cargo has disappeared without a trace. It's simply gone.",
                        .name = "The cargo has disappeared without a trace. It's simply gone.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -8,
                            },
                        },
                    },
                },
            },
            {
                .description = "Report it",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Authorities investigate and recover most of your cargo. You're reimbursed significantly.",
                        .name = "Authorities investigate and recover most of your cargo. You're reimbursed significantly.",
                        .chance = 60,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = 50,
                            },
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -5,
                            },
                        },
                    },
                    {
                        .description = "The bureaucratic investigation is exhausting and progress halts.",
                        .name = "The bureaucratic investigation is exhausting and progress halts.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Ignore loss",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 1,
                .outcomes = {
                    {
                        .description = "You mark the loss and move on pragmatically. Nothing changes, nothing stops.",
                        .name = "You mark the loss and move on pragmatically. Nothing changes, nothing stops.",
                        .chance = 100,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -5,
                            },
                        },
                    },
                },
            },
            {
                .description = "Track thief (Security)",
                .requirements = EV_FLAG_REQUIRES_SOLDIER,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your security team traces the theft to its source. You recover everything plus a bonus.",
                        .name = "Your security team traces the theft to its source. You recover everything plus a bonus.",
                        .chance = 80,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = 5,
                            },
                        },
                    },
                    {
                        .description = "The trail goes cold. You recover some items, but not all.",
                        .name = "The trail goes cold. You recover some items, but not all.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -3,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 37,
        .title = "Flames in the Void",
        .description = "Temperature gauges climb into the red. Your engines scream as thermal readings spike beyond safe limits. You smell scorched metal and ozone drifting through the ventilation. The chief engineer shouts over the alarms: 'Captain, we're about to blow! Do something!'",
        .option_count = 4,
        .options = {
            {
                .description = "Cool down",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your crew vents steam and reduces engine temperature. Normal operations continue unimpeded.",
                        .name = "Your crew vents steam and reduces engine temperature. Normal operations continue unimpeded.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The cooling process is difficult. The damage is mitigated but not prevented.",
                        .name = "The cooling process is difficult. The damage is mitigated but not prevented.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Push through",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your engines scream, but they hold. You arrive faster than expected despite the heat.",
                        .name = "Your engines scream, but they hold. You arrive faster than expected despite the heat.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                    {
                        .description = "You push too hard. Metal fails spectacularly under thermal stress.",
                        .name = "You push too hard. Metal fails spectacularly under thermal stress.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -3,
                            },
                        },
                    },
                },
            },
            {
                .description = "Reduce load",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Lighter cargo reduces engine strain significantly. Temperature normalizes.",
                        .name = "Lighter cargo reduces engine strain significantly. Temperature normalizes.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -3,
                            },
                        },
                    },
                    {
                        .description = "Even with reduced weight, the engines remain dangerously hot. You lose cargo for little gain.",
                        .name = "Even with reduced weight, the engines remain dangerously hot. You lose cargo for little gain.",
                        .chance = 40,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -8,
                            },
                        },
                    },
                },
            },
            {
                .description = "Optimize cooling (Engineer)",
                .requirements = EV_FLAG_REQUIRES_ENGINEER,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your engineer supercharges the cooling systems. Engine performance improves beyond baseline.",
                        .name = "Your engineer supercharges the cooling systems. Engine performance improves beyond baseline.",
                        .chance = 80,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Partial optimization is achieved. Cooling improves, but your overheating remains a concern.",
                        .name = "Partial optimization is achieved. Cooling improves, but your overheating remains a concern.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 38,
        .title = "Crushing Force",
        .description = "You enter a system that your databases said would be routine, but something is horrifically wrong. Gravity fields slam into your ship like a fist-stronger, far stronger than anything the local stellar bodies should produce. Your ship groans under the impossible strain. Something here defies known physics.",
        .option_count = 4,
        .options = {
            {
                .description = "Adjust thrusters",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your pilot makes delicate thruster adjustments. You descend smoothly despite the crushing gravity.",
                        .name = "Your pilot makes delicate thruster adjustments. You descend smoothly despite the crushing gravity.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The gravity is stronger than compensated for. Your ship shudders and takes damage.",
                        .name = "The gravity is stronger than compensated for. Your ship shudders and takes damage.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -3,
                            },
                        },
                    },
                },
            },
            {
                .description = "Avoid the area",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Prudent routing around the anomaly keeps you safe from harm.",
                        .name = "Prudent routing around the anomaly keeps you safe from harm.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The detour consumes fuel that you can't spare.",
                        .name = "The detour consumes fuel that you can't spare.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Push forward",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your crew braves the crushing forces and emerges victorious. The experience hardens them.",
                        .name = "Your crew braves the crushing forces and emerges victorious. The experience hardens them.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_XP,
                                .value = 20,
                            },
                        },
                    },
                    {
                        .description = "The gravity is more intense than anticipated. Your ship shudders and takes damage.",
                        .name = "The gravity is more intense than anticipated. Your ship shudders and takes damage.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Pilot adjust (Pilot)",
                .requirements = EV_FLAG_REQUIRES_PILOT,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your pilot's mastery of gravity fields is stunning. You gain extra speed and efficiency.",
                        .name = "Your pilot's mastery of gravity fields is stunning. You gain extra speed and efficiency.",
                        .chance = 80,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = 1,
                            },
                        },
                    },
                    {
                        .description = "The adjustment is challenging. You maintain course but expend extra energy.",
                        .name = "The adjustment is challenging. You maintain course but expend extra energy.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 41,
        .title = "Diamonds in Darkness",
        .description = "Your contact transmits an encrypted message: 'I have a shipment that others will pay handsomely to intercept. Transport it to the outer colonies, no questions asked. The profits would set you up for years... but so would the risk if you're caught.'",
        .option_count = 4,
        .options = {
            {
                .description = "Accept",
                .requirements = EV_FLAG_REQUIRES_FUEL,
                .required_count = 2,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "The contract pays spectacularly. Your coffers overflow with credits... but you've made enemies.",
                        .name = "The contract pays spectacularly. Your coffers overflow with credits... but you've made enemies.",
                        .chance = 60,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = 90,
                            },
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -2,
                            },
                        },
                    },
                    {
                        .description = "The authorities catch you. Severe penalties and complications follow.",
                        .name = "The authorities catch you. Severe penalties and complications follow.",
                        .chance = 40,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = -10,
                            },
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Decline",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 1,
                .outcomes = {
                    {
                        .description = "You turn them down politely. No complications, no entanglement.",
                        .name = "You turn them down politely. No complications, no entanglement.",
                        .chance = 100,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Negotiate",
                .requirements = EV_FLAG_REQUIRES_FUEL,
                .required_count = 2,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your negotiation skills secure more favorable terms. The reward increases significantly.",
                        .name = "Your negotiation skills secure more favorable terms. The reward increases significantly.",
                        .chance = 60,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = 130,
                            },
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -2,
                            },
                        },
                    },
                    {
                        .description = "They refuse to improve their offer. You take it or leave it.",
                        .name = "They refuse to improve their offer. You take it or leave it.",
                        .chance = 40,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = 90,
                            },
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Secure route (Pilot)",
                .requirements = EV_FLAG_REQUIRES_PILOT,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your pilot charts a route that's both safe and profitable. The delivery succeeds cleanly.",
                        .name = "Your pilot charts a route that's both safe and profitable. The delivery succeeds cleanly.",
                        .chance = 80,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = 125,
                            },
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -1,
                            },
                        },
                    },
                    {
                        .description = "The route is safer, but enforcement patrols still get a sniff. Minor close calls occur.",
                        .name = "The route is safer, but enforcement patrols still get a sniff. Minor close calls occur.",
                        .chance = 20,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = -5,
                            },
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 42,
        .title = "Casualties of Transit",
        .description = "Jump trauma rattled your hull; one precious crate cracked open and its contents scattered in the hold. The crew scrambles: can you salvage value from chaos, or has this cargo run been ruined?",
        .option_count = 4,
        .options = {
            {
                .description = "Repair crate",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your engineers mend the crate and seal the shipment. Most cargo survives intact.",
                        .name = "Your engineers mend the crate and seal the shipment. Most cargo survives intact.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -2,
                            },
                        },
                    },
                    {
                        .description = "Repair materials prove more scarce than expected; you pay dearly in resources.",
                        .name = "Repair materials prove more scarce than expected; you pay dearly in resources.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -5,
                            },
                        },
                    },
                },
            },
            {
                .description = "Transfer contents",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Meticulous manual transfer recovers the bulk of goods, while the damaged few are quarantined.",
                        .name = "Meticulous manual transfer recovers the bulk of goods, while the damaged few are quarantined.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -2,
                            },
                        },
                    },
                    {
                        .description = "Chaos and clumsiness cause additional spillage. The effort saves little.",
                        .name = "Chaos and clumsiness cause additional spillage. The effort saves little.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -5,
                            },
                        },
                    },
                },
            },
            {
                .description = "Discard",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You throw the ruined crate away and avoid contamination, preserving the rest of the hold.",
                        .name = "You throw the ruined crate away and avoid contamination, preserving the rest of the hold.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -3,
                            },
                        },
                    },
                    {
                        .description = "The loss is steep, but it removes the hazard and allows flight to continue.",
                        .name = "The loss is steep, but it removes the hazard and allows flight to continue.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -5,
                            },
                        },
                    },
                },
            },
            {
                .description = "Reinforce (Engineer)",
                .requirements = EV_FLAG_REQUIRES_ENGINEER,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your engineer reinforces the crate with improvised plating. It survives and delivers valuable cargo.",
                        .name = "Your engineer reinforces the crate with improvised plating. It survives and delivers valuable cargo.",
                        .chance = 80,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The reinforcement takes longer than expected and slows your departure.",
                        .name = "The reinforcement takes longer than expected and slows your departure.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -3,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 43,
        .title = "Illegal Inspection",
        .description = "Shadowy enforcement agents materialize at your airlock, clipboard in hand and blaster at their sides. They demand to board without jurisdiction-this is a dangerous grey market encounter.",
        .option_count = 4,
        .options = {
            {
                .description = "Comply",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You play the honest trader. The inspectors leave grudgingly convinced and your reputation improves.",
                        .name = "You play the honest trader. The inspectors leave grudgingly convinced and your reputation improves.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = 10,
                            },
                        },
                    },
                    {
                        .description = "Their over-zealous search finds contraband. They confiscate cargo and write a fine.",
                        .name = "Their over-zealous search finds contraband. They confiscate cargo and write a fine.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -5,
                            },
                        },
                    },
                },
            },
            {
                .description = "Deny access",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You slam the hatch shut and refuse entry. The agents grumble and move on.",
                        .name = "You slam the hatch shut and refuse entry. The agents grumble and move on.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = 5,
                            },
                        },
                    },
                    {
                        .description = "They force their way in, and a scuffle damages your hull.",
                        .name = "They force their way in, and a scuffle damages your hull.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Flee",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You jump to lightspeed before they're ready. They lose you in the stars.",
                        .name = "You jump to lightspeed before they're ready. They lose you in the stars.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = 5,
                            },
                        },
                    },
                    {
                        .description = "They pursue and manage a hit, leaving your hull scorched.",
                        .name = "They pursue and manage a hit, leaving your hull scorched.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Bribe",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "A crisp envelope changes hands. They leave with a wink.",
                        .name = "A crisp envelope changes hands. They leave with a wink.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = -25,
                            },
                        },
                    },
                    {
                        .description = "They demand more and take cash anyway. You bleed funds.",
                        .name = "They demand more and take cash anyway. You bleed funds.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = -50,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 44,
        .title = "Broken Navigation Beacon",
        .description = "The trusted local nav beacon has gone dark. Charts now show empty void where warnings used to be. You must choose between speed, risk, and caution.",
        .option_count = 4,
        .options = {
            {
                .description = "Proceed blindly",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Careful instincts guide you with surprising accuracy and you gain ground quickly.",
                        .name = "Careful instincts guide you with surprising accuracy and you gain ground quickly.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Without the beacon, your pilot misjudges a turn and the hull grazes asteroid debris.",
                        .name = "Without the beacon, your pilot misjudges a turn and the hull grazes asteroid debris.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Wait for repair",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You wait. The beacon is repaired and the route is secure.",
                        .name = "You wait. The beacon is repaired and the route is secure.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Your patience pays off, and you avoid danger by staying put.",
                        .name = "Your patience pays off, and you avoid danger by staying put.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                },
            },
            {
                .description = "Use backup",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Backup navigators keep you on course, though not as efficiently as the official beacon.",
                        .name = "Backup navigators keep you on course, though not as efficiently as the official beacon.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -1,
                            },
                        },
                    },
                    {
                        .description = "The fallback guidance is outdated, causing extra fuel consumption.",
                        .name = "The fallback guidance is outdated, causing extra fuel consumption.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Calibrate (Pilot)",
                .requirements = EV_FLAG_REQUIRES_PILOT,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your pilot throws the nav system into a fine-tuned state and achieves near-perfect tracking.",
                        .name = "Your pilot throws the nav system into a fine-tuned state and achieves near-perfect tracking.",
                        .chance = 80,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Even expert pilots can only do so much; you drift slightly and burn extra fuel.",
                        .name = "Even expert pilots can only do so much; you drift slightly and burn extra fuel.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 45,
        .title = "Mysterious Illness",
        .description = "One by one, crew members begin coughing blood and vomiting teal foam. The medical bay is full. No one knows whether this is contagion, radiation, or something alien. Time and treatment are both critical.",
        .option_count = 3,
        .options = {
            {
                .description = "Quarantine",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your quick action prevents spread, though one crew member still succumbs.",
                        .name = "Your quick action prevents spread, though one crew member still succumbs.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                    {
                        .description = "The sickness already reached too far. Lives are lost despite containment.",
                        .name = "The sickness already reached too far. Lives are lost despite containment.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Ignore",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You risk it and keep moving. No one else gets sick immediately, but tensions rise.",
                        .name = "You risk it and keep moving. No one else gets sick immediately, but tensions rise.",
                        .chance = 60,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = -5,
                            },
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                    {
                        .description = "Unchecked, the illness explodes through the crew. Many fall ill.",
                        .name = "Unchecked, the illness explodes through the crew. Many fall ill.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -3,
                            },
                        },
                    },
                },
            },
            {
                .description = "Cure it (Medic)",
                .requirements = EV_FLAG_REQUIRES_MEDIC,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your medic identifies an antidote from ship stores. Recovery begins rapidly.",
                        .name = "Your medic identifies an antidote from ship stores. Recovery begins rapidly.",
                        .chance = 80,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The experimental treatment backfires; the crew suffers uncertainty.",
                        .name = "The experimental treatment backfires; the crew suffers uncertainty.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 47,
        .title = "Hostile Vessel on Approach",
        .description = "Your radar catches a sleek, black destroyer closing fast. Its signal pings in a known pirate frequency. The HUD flashes red: prepare for possible combat or parley.",
        .option_count = 4,
        .options = {
            {
                .description = "Negotiate",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You offer tribute and they accept. Peace is bought at a cost.",
                        .name = "You offer tribute and they accept. Peace is bought at a cost.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = -10,
                            },
                        },
                    },
                    {
                        .description = "The negotiations stall, and the enemy makes their move.",
                        .name = "The negotiations stall, and the enemy makes their move.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Evade",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You launch a daring escape through tight asteroid lanes and they fail to follow.",
                        .name = "You launch a daring escape through tight asteroid lanes and they fail to follow.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "They anticipate your escape vector and pin you down.",
                        .name = "They anticipate your escape vector and pin you down.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -3,
                            },
                        },
                    },
                },
            },
            {
                .description = "Fight",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You fight with naval precision and drive them off, though your hull is scarred.",
                        .name = "You fight with naval precision and drive them off, though your hull is scarred.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                    {
                        .description = "Their firepower is overwhelming. Your ship is wounded in the exchange.",
                        .name = "Their firepower is overwhelming. Your ship is wounded in the exchange.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -3,
                            },
                        },
                    },
                },
            },
            {
                .description = "Call for backup (Security)",
                .requirements = EV_FLAG_REQUIRES_SOLDIER,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Support arrives as if on cue. The hostile ship is routed.",
                        .name = "Support arrives as if on cue. The hostile ship is routed.",
                        .chance = 80,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Backup arrives late. You fend them off but not without minor damage.",
                        .name = "Backup arrives late. You fend them off but not without minor damage.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 50,
        .title = "Ancient Defense System",
        .description = "As you explore the ancient ruins, dormant turrets roar to life and laser grids snap into place. Your ship is suddenly the target of a long-dead civilizations automated guardian.",
        .option_count = 4,
        .options = {
            {
                .description = "Evade",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You weave through beams and evade the worst of it, minimizing damage.",
                        .name = "You weave through beams and evade the worst of it, minimizing damage.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                    {
                        .description = "A stray pulse hits your forward plating and your hull is peppered with holes.",
                        .name = "A stray pulse hits your forward plating and your hull is peppered with holes.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -3,
                            },
                        },
                    },
                },
            },
            {
                .description = "Defend",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your ship hold and your crew returns fire, disabling several turrets.",
                        .name = "Your ship hold and your crew returns fire, disabling several turrets.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                    {
                        .description = "The laser barrage is relentless; your hull takes heavy punishment.",
                        .name = "The laser barrage is relentless; your hull takes heavy punishment.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -3,
                            },
                        },
                    },
                },
            },
            {
                .description = "Retreat",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You disengage and pull out of range, burning some extra fuel to flee.",
                        .name = "You disengage and pull out of range, burning some extra fuel to flee.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -1,
                            },
                        },
                    },
                    {
                        .description = "Retreat is messy; the automated systems fire as you go, scraping your hull.",
                        .name = "Retreat is messy; the automated systems fire as you go, scraping your hull.",
                        .chance = 40,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Hack system (Scientist)",
                .requirements = EV_FLAG_REQUIRES_SCIENTIST,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your scientist overrides the ruins' AI and turns the defenses against false targets.",
                        .name = "Your scientist overrides the ruins' AI and turns the defenses against false targets.",
                        .chance = 80,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = 1,
                            },
                        },
                    },
                    {
                        .description = "The system resists the hack and retaliates with focused beams.",
                        .name = "The system resists the hack and retaliates with focused beams.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 51,
        .title = "Hull Breach",
        .description = "A whistling rupture tears open your hull and an aft corridor disappears into black vacuum. Alarms shriek. Your crew's lives hang by a thread.",
        .option_count = 4,
        .options = {
            {
                .description = "Seal bulkheads immediately",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your rapid response locks down the breach before more air is lost. The crew nods in relief.",
                        .name = "Your rapid response locks down the breach before more air is lost. The crew nods in relief.",
                        .chance = 70,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                    {
                        .description = "The breach spreads faster than your seals can deploy, costing a life.",
                        .name = "The breach spreads faster than your seals can deploy, costing a life.",
                        .chance = 30,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Rescue exposed crew",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "A daring tether rescue pulls everyone back in. You've earned a hero's reputation.",
                        .name = "A daring tether rescue pulls everyone back in. You've earned a hero's reputation.",
                        .chance = 50,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = 10,
                            },
                        },
                    },
                    {
                        .description = "The vacuum claims two as the rescue attempt goes badly.",
                        .name = "The vacuum claims two as the rescue attempt goes badly.",
                        .chance = 50,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Ignore and stabilize ship",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You sacrifice the damaged section and stabilize the vessel. Minimal further harm.",
                        .name = "You sacrifice the damaged section and stabilize the vessel. Minimal further harm.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                    {
                        .description = "Inaction leads to additional casualties. The crew is shaken.",
                        .name = "Inaction leads to additional casualties. The crew is shaken.",
                        .chance = 40,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Emergency patch (Engineer)",
                .requirements = EV_FLAG_REQUIRES_ENGINEER,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your engineer's clamp works perfectly; the breach is sealed instantly.",
                        .name = "Your engineer's clamp works perfectly; the breach is sealed instantly.",
                        .chance = 80,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                    {
                        .description = "The patch holds but the rush causes an injury. One crew member is lost.",
                        .name = "The patch holds but the rush causes an injury. One crew member is lost.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 52,
        .title = "Radiation Surge",
        .description = "A sudden wave of star-borne gamma radiation engulfs the cargo bay during inspection. Geiger counters flash madly, and crew in under-pressure suits stumble. This is a race between shields and fallout.",
        .option_count = 4,
        .options = {
            {
                .description = "Evacuate immediately",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You shepherd everyone out. One crew member is exposed before the hatch slams.",
                        .name = "You shepherd everyone out. One crew member is exposed before the hatch slams.",
                        .chance = 70,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                    {
                        .description = "The evacuation is too slow; the blast affects one person fatally.",
                        .name = "The evacuation is too slow; the blast affects one person fatally.",
                        .chance = 30,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Shield cargo",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Cargo holds, and the loss is limited to a brief dose to ground crew.",
                        .name = "Cargo holds, and the loss is limited to a brief dose to ground crew.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The shielding is inadequate. The crew suffers exposure despite your best effort.",
                        .name = "The shielding is inadequate. The crew suffers exposure despite your best effort.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Push through",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You persevere through the surge and finish locking down the cargo before more interference hits.",
                        .name = "You persevere through the surge and finish locking down the cargo before more interference hits.",
                        .chance = 50,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The radiation burns through armor. A crew member is lost.",
                        .name = "The radiation burns through armor. A crew member is lost.",
                        .chance = 50,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Calibrate shields (Scientist)",
                .requirements = EV_FLAG_REQUIRES_SCIENTIST,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your scientist perfects the pattern and the surge is routed safely.",
                        .name = "Your scientist perfects the pattern and the surge is routed safely.",
                        .chance = 80,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -1,
                            },
                        },
                    },
                    {
                        .description = "The calibration is imperfect; the crew takes a minor hit.",
                        .name = "The calibration is imperfect; the crew takes a minor hit.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 53,
        .title = "Hostile Boarding",
        .description = "Pirate grapples hook into your hull and boarding ladders unfurl. Raiders blow past defenses into your corridor. Battle for the ship begins in the dark.",
        .option_count = 4,
        .options = {
            {
                .description = "Fight them off",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your crew forms a fighting line and drives the invaders back with fire and steel.",
                        .name = "Your crew forms a fighting line and drives the invaders back with fire and steel.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = 10,
                            },
                        },
                    },
                    {
                        .description = "The door is breached and the cost is blood. You lose a team member.",
                        .name = "The door is breached and the cost is blood. You lose a team member.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Flee",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You jump to hyperspace with jump drives screaming. The pirates can't follow.",
                        .name = "You jump to hyperspace with jump drives screaming. The pirates can't follow.",
                        .chance = 70,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -1,
                            },
                        },
                    },
                    {
                        .description = "In the rush to escape, a rear guard is left behind and lost.",
                        .name = "In the rush to escape, a rear guard is left behind and lost.",
                        .chance = 30,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Surrender cargo",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You trade goods for your crew's heads. The pirates haul away and vanish.",
                        .name = "You trade goods for your crew's heads. The pirates haul away and vanish.",
                        .chance = 80,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -10,
                            },
                        },
                    },
                    {
                        .description = "They greedily take hostages anyway for a later ransom.",
                        .name = "They greedily take hostages anyway for a later ransom.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Defensive tactics (Security)",
                .requirements = EV_FLAG_REQUIRES_SOLDIER,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your security teams execute perfect countermeasures. Boarding is repelled cleanly.",
                        .name = "Your security teams execute perfect countermeasures. Boarding is repelled cleanly.",
                        .chance = 85,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = 15,
                            },
                        },
                    },
                    {
                        .description = "A panic moment causes one casualty, but the ship lives.",
                        .name = "A panic moment causes one casualty, but the ship lives.",
                        .chance = 15,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 54,
        .title = "Toxic Atmosphere",
        .description = "A corrosive vapor leaks from an unknown source; alarms strobe and the air tastes of metal and bleach. You must contain it before it overwhelms your lungs.",
        .option_count = 3,
        .options = {
            {
                .description = "Use suits",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your crew dons emergency anti-toxin suits and works carefully. The risk is averted.",
                        .name = "Your crew dons emergency anti-toxin suits and works carefully. The risk is averted.",
                        .chance = 70,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "One suit malfunctions. A crew member suffocates despite your best effort.",
                        .name = "One suit malfunctions. A crew member suffocates despite your best effort.",
                        .chance = 30,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Work quickly and fix the leak",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Rapid action seals the source. You breathe easier and gain a hard-fought victory.",
                        .name = "Rapid action seals the source. You breathe easier and gain a hard-fought victory.",
                        .chance = 50,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The leak is stubborn. A crew member succumbs to exposure in the rush.",
                        .name = "The leak is stubborn. A crew member succumbs to exposure in the rush.",
                        .chance = 50,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Filter toxins (Engineer)",
                .requirements = EV_FLAG_REQUIRES_ENGINEER,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your engineer tunes the filters to maximum efficiency and clears the air quickly.",
                        .name = "Your engineer tunes the filters to maximum efficiency and clears the air quickly.",
                        .chance = 75,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Filters cover most of it, but one toxic patch slips through.",
                        .name = "Filters cover most of it, but one toxic patch slips through.",
                        .chance = 25,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 55,
        .title = "Crew Mutiny",
        .description = "Whispers spread through the crew. Some demand action, others bristle at leadership. If this standoff explodes, your voyage may end in blood.",
        .option_count = 4,
        .options = {
            {
                .description = "Negotiate",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You broker a compromise. The crew calms and respect for your command is restored.",
                        .name = "You broker a compromise. The crew calms and respect for your command is restored.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = 10,
                            },
                        },
                    },
                    {
                        .description = "Negotiations collapse into fistfights, and one crew member is lost.",
                        .name = "Negotiations collapse into fistfights, and one crew member is lost.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Suppress forcefully",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your loyal security detains the mutineers and order returns.",
                        .name = "Your loyal security detains the mutineers and order returns.",
                        .chance = 70,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The suppression turns brutal; rebels fall and morale fractures.",
                        .name = "The suppression turns brutal; rebels fall and morale fractures.",
                        .chance = 30,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Give concessions",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You make difficult compromises. The crew cheers, but you spend resources to keep them content.",
                        .name = "You make difficult compromises. The crew cheers, but you spend resources to keep them content.",
                        .chance = 80,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = -30,
                            },
                        },
                    },
                    {
                        .description = "Your concessions are seen as weakness; mutiny plots deepen.",
                        .name = "Your concessions are seen as weakness; mutiny plots deepen.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Command authority (Security)",
                .requirements = EV_FLAG_REQUIRES_SOLDIER,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "A show of force and a firm command voice ends the uprising quickly.",
                        .name = "A show of force and a firm command voice ends the uprising quickly.",
                        .chance = 85,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = 15,
                            },
                        },
                    },
                    {
                        .description = "The tactic saves the ship, but one life is lost in the chaos.",
                        .name = "The tactic saves the ship, but one life is lost in the chaos.",
                        .chance = 15,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 56,
        .title = "Alien Parasite",
        .description = "A crewman collapses with wet, black tendrils moving under their skin. The ship's biohazard sensors scream. This parasite is not from any known biology.",
        .option_count = 4,
        .options = {
            {
                .description = "Quarantine them",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "The split-level quarantine holds. The parasite is locked away.",
                        .name = "The split-level quarantine holds. The parasite is locked away.",
                        .chance = 70,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "It breaks containment and infects another crew member.",
                        .name = "It breaks containment and infects another crew member.",
                        .chance = 30,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Eject infected",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your auto-lock releases the infected pod into open space. You save the ship at a harsh cost.",
                        .name = "Your auto-lock releases the infected pod into open space. You save the ship at a harsh cost.",
                        .chance = 90,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                    {
                        .description = "It bursts before ejection and spores scatter. The parasite jumps to two more.",
                        .name = "It bursts before ejection and spores scatter. The parasite jumps to two more.",
                        .chance = 10,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Do nothing",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Strangely, the parasite goes dormant. You continue with uneasy calm.",
                        .name = "Strangely, the parasite goes dormant. You continue with uneasy calm.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "It spreads like wildfire and cripples your crew.",
                        .name = "It spreads like wildfire and cripples your crew.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Treat infection (Medic)",
                .requirements = EV_FLAG_REQUIRES_MEDIC,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "A medic develops an antiparasitic regimen. The crew's faith in your leadership is renewed.",
                        .name = "A medic develops an antiparasitic regimen. The crew's faith in your leadership is renewed.",
                        .chance = 80,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = 10,
                            },
                        },
                    },
                    {
                        .description = "The treatment is not enough. One life is still lost.",
                        .name = "The treatment is not enough. One life is still lost.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 58,
        .title = "High-Speed Maneuver",
        .description = "An opening appears in asteroid traffic, but it's narrow and uncharted. You must choose between careful pacing and a dangerous sprint. Heroics or catastrophe await.",
        .option_count = 3,
        .options = {
            {
                .description = "Take it slow",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You thread the route cautiously and arrive intact.",
                        .name = "You thread the route cautiously and arrive intact.",
                        .chance = 80,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Despite caution, a loose fragment clips your hull.",
                        .name = "Despite caution, a loose fragment clips your hull.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Push limits",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your risk pays off and you fly through with blazing speed.",
                        .name = "Your risk pays off and you fly through with blazing speed.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = 1,
                            },
                        },
                    },
                    {
                        .description = "The maneuver is too aggressive. You smash a wing and suffer heavy damage.",
                        .name = "The maneuver is too aggressive. You smash a wing and suffer heavy damage.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -3,
                            },
                        },
                    },
                },
            },
            {
                .description = "Precision navigation (Pilot)",
                .requirements = EV_FLAG_REQUIRES_PILOT,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your pilot's calculations are perfect. The move becomes a legend in your logbook.",
                        .name = "Your pilot's calculations are perfect. The move becomes a legend in your logbook.",
                        .chance = 85,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = 10,
                            },
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = 1,
                            },
                        },
                    },
                    {
                        .description = "Even precision cannot account for a rogue rock. Minor hull damage occurs.",
                        .name = "Even precision cannot account for a rogue rock. Minor hull damage occurs.",
                        .chance = 15,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 59,
        .title = "Explosive Cargo",
        .description = "A dull thump turns into a heartbeat. Your cargo being starts to hiss and glow. One wrong move and your hold becomes a warhead.",
        .option_count = 4,
        .options = {
            {
                .description = "Dump cargo",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You eject the volatile containers safely. The blast occurs far behind you.",
                        .name = "You eject the volatile containers safely. The blast occurs far behind you.",
                        .chance = 90,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -10,
                            },
                        },
                    },
                    {
                        .description = "An explosion rips through the ejected mass before it clears. Shockwaves hit your hull.",
                        .name = "An explosion rips through the ejected mass before it clears. Shockwaves hit your hull.",
                        .chance = 10,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -5,
                            },
                        },
                    },
                },
            },
            {
                .description = "Stabilize it",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your crew applies cooling and dampeners; the materials settle.",
                        .name = "Your crew applies cooling and dampeners; the materials settle.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The booms begin despite your skillful work. The ship shudders through the blast.",
                        .name = "The booms begin despite your skillful work. The ship shudders through the blast.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Ignore",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Miraculously, the cargo is inert and nothing happens.",
                        .name = "Miraculously, the cargo is inert and nothing happens.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The hold explodes, and the ship nearly tears apart.",
                        .name = "The hold explodes, and the ship nearly tears apart.",
                        .chance = 60,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -3,
                            },
                        },
                    },
                },
            },
            {
                .description = "Disarm safely (Engineer)",
                .requirements = EV_FLAG_REQUIRES_ENGINEER,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your engineer's deft hands neutralize the charges with zero incidents.",
                        .name = "Your engineer's deft hands neutralize the charges with zero incidents.",
                        .chance = 85,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "A stray spark triggers a partial blast. One crew member is hurt.",
                        .name = "A stray spark triggers a partial blast. One crew member is hurt.",
                        .chance = 15,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 60,
        .title = "Lost in Storm",
        .description = "Lightning spikes and gravitational chaos toss your hull like a toy. Your navigation instruments spin and starfields warp. You must decide whether to fight it or wait.",
        .option_count = 3,
        .options = {
            {
                .description = "Wait it out",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "The storm eventually calms and your ship is intact.",
                        .name = "The storm eventually calms and your ship is intact.",
                        .chance = 70,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The storm rips your sensors apart and you're lost in the void.",
                        .name = "The storm rips your sensors apart and you're lost in the void.",
                        .chance = 30,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Push forward",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You barrel through with grit. Progress is made despite the turmoil.",
                        .name = "You barrel through with grit. Progress is made despite the turmoil.",
                        .chance = 50,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The storm punches through your wing. You take hull damage.",
                        .name = "The storm punches through your wing. You take hull damage.",
                        .chance = 50,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Navigate storm (Pilot)",
                .requirements = EV_FLAG_REQUIRES_PILOT,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your pilot reads the storm like a poem and finds a calm corridor.",
                        .name = "Your pilot reads the storm like a poem and finds a calm corridor.",
                        .chance = 85,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "A sudden vortex catches you; minor hull stress results.",
                        .name = "A sudden vortex catches you; minor hull stress results.",
                        .chance = 15,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 61,
        .title = "Sabotaged Systems",
        .description = "Alarms blare as critical subsystems fail without warning. Someone with inside access is rerouting your power. You've been sabotaged in the middle of flight.",
        .option_count = 4,
        .options = {
            {
                .description = "Repair systems",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You identify the damaged modules and patch them quickly, restoring function.",
                        .name = "You identify the damaged modules and patch them quickly, restoring function.",
                        .chance = 70,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Your repairs come moments too late; a cascade damages the hull.",
                        .name = "Your repairs come moments too late; a cascade damages the hull.",
                        .chance = 30,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Shut everything down",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "A cold reboot halts the sabotage and lets you diagnose the issue.",
                        .name = "A cold reboot halts the sabotage and lets you diagnose the issue.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Partial systems collapse as you reboot, causing one critical failure.",
                        .name = "Partial systems collapse as you reboot, causing one critical failure.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Ignore sabotage",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You carry on and it somehow holds. The risk is enormous, but you survive.",
                        .name = "You carry on and it somehow holds. The risk is enormous, but you survive.",
                        .chance = 40,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The sabotage spreads and a system fails catastrophically.",
                        .name = "The sabotage spreads and a system fails catastrophically.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Trace saboteur (Security)",
                .requirements = EV_FLAG_REQUIRES_SOLDIER,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your security team catches the culprit and prevents further damage.",
                        .name = "Your security team catches the culprit and prevents further damage.",
                        .chance = 80,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = 10,
                            },
                        },
                    },
                    {
                        .description = "The saboteur fights back. One systems engineer is lost in the crossfire.",
                        .name = "The saboteur fights back. One systems engineer is lost in the crossfire.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 63,
        .title = "Derelict Trap",
        .description = "You spot a drifting warship, marred by age and battle scars-too tempting for a salvage run. This could be winnings or a baited killzone. Your sensors warn of decay and hidden mines.",
        .option_count = 4,
        .options = {
            {
                .description = "Investigate",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You slip aboard and strip out the cargo, finding rare goods before attackers appear.",
                        .name = "You slip aboard and strip out the cargo, finding rare goods before attackers appear.",
                        .chance = 60,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = 100,
                            },
                        },
                    },
                    {
                        .description = "Pirates spring from the shadows and youre ambushed mid-salvage.",
                        .name = "Pirates spring from the shadows and youre ambushed mid-salvage.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Avoid it",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You choose caution. The ship drifts away, and you avoid possible death.",
                        .name = "You choose caution. The ship drifts away, and you avoid possible death.",
                        .chance = 90,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "It was an ambush after all. You miss the trap but lose out on potential salvage.",
                        .name = "It was an ambush after all. You miss the trap but lose out on potential salvage.",
                        .chance = 10,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Salvage quickly",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You rush in, grab the best salvage, and jump out before the trap snaps.",
                        .name = "You rush in, grab the best salvage, and jump out before the trap snaps.",
                        .chance = 50,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = 500,
                            },
                        },
                    },
                    {
                        .description = "The trap triggers within seconds; one crew member is lost in the explosion.",
                        .name = "The trap triggers within seconds; one crew member is lost in the explosion.",
                        .chance = 50,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Scan first (Scientist)",
                .requirements = EV_FLAG_REQUIRES_SCIENTIST,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your scan reveals the hidden triggers and you deactivate them, securing high-value loot.",
                        .name = "Your scan reveals the hidden triggers and you deactivate them, securing high-value loot.",
                        .chance = 85,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREDITS,
                                .value = 80,
                            },
                        },
                    },
                    {
                        .description = "You miss one trigger. A burst injures the boarding team.",
                        .name = "You miss one trigger. A burst injures the boarding team.",
                        .chance = 15,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 64,
        .title = "Escape Pod Decision",
        .description = "One of your crew radiates a desperate distress call from an escape pod drifting in the void-separated during a hull breach. Their panicked voice crackles through comms: 'Captain, I'm out here... please, don't leave me.' Life support is failing fast.",
        .option_count = 4,
        .options = {
            {
                .description = "Rescue them",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your team executes a flawless rescue. They return safely, bearing gratitude and loyalty.",
                        .name = "Your team executes a flawless rescue. They return safely, bearing gratitude and loyalty.",
                        .chance = 70,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = 10,
                            },
                        },
                    },
                    {
                        .description = "The rescue attempt takes a tragic turn. One of your rescuers doesn't come back.",
                        .name = "The rescue attempt takes a tragic turn. One of your rescuers doesn't come back.",
                        .chance = 30,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Leave them",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You continue the mission, hardening your heart. Reputation suffers but the mission succeeds.",
                        .name = "You continue the mission, hardening your heart. Reputation suffers but the mission succeeds.",
                        .chance = 90,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = -10,
                            },
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                    {
                        .description = "The crew is devastated. Morale collapses as guilt consumes them. Your reputation becomes toxic.",
                        .name = "The crew is devastated. Morale collapses as guilt consumes them. Your reputation becomes toxic.",
                        .chance = 10,
                        .effect_count = 2,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = -20,
                            },
                        },
                    },
                },
            },
            {
                .description = "Send drone",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your drone works perfectly. The stranded crew member is retrieved without risk.",
                        .name = "Your drone works perfectly. The stranded crew member is retrieved without risk.",
                        .chance = 60,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "The drone malfunctions during retrieval. Your crew member is lost before you can respond.",
                        .name = "The drone malfunctions during retrieval. Your crew member is lost before you can respond.",
                        .chance = 40,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Coordinate rescue (Pilot)",
                .requirements = EV_FLAG_REQUIRES_PILOT,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your pilot orchestrates a textbook rescue. Your stranded crew member returns safely, forever grateful.",
                        .name = "Your pilot orchestrates a textbook rescue. Your stranded crew member returns safely, forever grateful.",
                        .chance = 85,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_REPUTATION,
                                .value = 15,
                            },
                        },
                    },
                    {
                        .description = "A miscalculation in the rescue vector costs a life. Your crew member is lost anyway.",
                        .name = "A miscalculation in the rescue vector costs a life. Your crew member is lost anyway.",
                        .chance = 15,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
    {
        .id = 65,
        .title = "Experimental Tech Failure",
        .description = "Alarms shriek through engineering as the experimental quantum flux module overloads. Containment fields flicker erratically, casting eerie blue glows while sparks explode from consoles. The air reeks of burning circuits. This promised breakthrough has become a catastrophic threat.",
        .option_count = 4,
        .options = {
            {
                .description = "Shut it down",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "You power down the module carefully. It winds down safely.",
                        .name = "You power down the module carefully. It winds down safely.",
                        .chance = 70,
                        .effect_count = 0,
                        .effects = {
                        },
                    },
                    {
                        .description = "Powering it down causes a cascade reaction. An explosion rocks your engineering bay.",
                        .name = "Powering it down causes a cascade reaction. An explosion rocks your engineering bay.",
                        .chance = 30,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -1,
                            },
                        },
                    },
                },
            },
            {
                .description = "Keep using it",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "The module runs beautifully, delivering performance beyond specifications. The cargo is now more valuable.",
                        .name = "The module runs beautifully, delivering performance beyond specifications. The cargo is now more valuable.",
                        .chance = 50,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = 2,
                            },
                        },
                    },
                    {
                        .description = "Without warning, the system explodes catastrophically. You lose multiple crew members.",
                        .name = "Without warning, the system explodes catastrophically. You lose multiple crew members.",
                        .chance = 50,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CREW,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Remove module",
                .requirements = 0,
                .required_count = 0,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your engineers carefully extract the module from the system. No damage occurs.",
                        .name = "Your engineers carefully extract the module from the system. No damage occurs.",
                        .chance = 80,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_CARGO,
                                .value = -1,
                            },
                        },
                    },
                    {
                        .description = "During removal, a coolant line ruptures. Dangerous fluids spray across the compartment.",
                        .name = "During removal, a coolant line ruptures. Dangerous fluids spray across the compartment.",
                        .chance = 20,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -2,
                            },
                        },
                    },
                },
            },
            {
                .description = "Stabilize tech (Scientist)",
                .requirements = EV_FLAG_REQUIRES_SCIENTIST,
                .required_count = 1,
                .outcome_count = 2,
                .outcomes = {
                    {
                        .description = "Your scientist stabilizes the exotic reactions. The module now runs reliably and efficiently.",
                        .name = "Your scientist stabilizes the exotic reactions. The module now runs reliably and efficiently.",
                        .chance = 85,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_FUEL,
                                .value = 1,
                            },
                        },
                    },
                    {
                        .description = "Stabilization efforts are only partially successful. Performance remains unpredictable.",
                        .name = "Stabilization efforts are only partially successful. Performance remains unpredictable.",
                        .chance = 15,
                        .effect_count = 1,
                        .effects = {
                            {
                                .type = EV_EFFECT_HULL,
                                .value = -1,
                            },
                        },
                    },
                },
            },
        },
    },
};
const int random_event_count = 47;
