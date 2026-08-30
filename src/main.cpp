// src/main.cpp — the REAL simulation, tying every teammate's piece together
//
// This creates 4 real bots, gives each one its own Portfolio (its personal
// stash of cash + shares), runs the market for a number of ticks, and after
// each tick asks every bot what it wants to do, then actually carries out
// that trade on its Portfolio. It also feeds live data to the dashboard.

#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>

#include "MarketEngine.h"
#include "NormalStrategy.h"
#include "CrashStrategy.h"
#include "Portfolio.h"
#include "DashboardObserver.h"

#include "MomentumBot.h"
#include "RandomBot.h"
#include "ValueBot.h"
#include "PanicBot.h"

// A small helper struct so we can keep each bot paired with its own
// Portfolio — Bot itself doesn't own a Portfolio, so we track that pairing
// here in main() instead.
struct BotEntry {
    std::unique_ptr<Bot> bot;
    Portfolio portfolio;
};

const std::string STOCK_NAME = "MMIND";   // the one stock everyone trades
const double STARTING_CASH   = 100000.0;  // Rs 1,00,000 per bot, same start for fairness
const int    SHARES_PER_TRADE = 10;       // fixed trade size, keeps things simple

int main() {
    // ---- 1. Set up the market ----
    MarketEngine* engine = MarketEngine::getInstance(100.0); // starting price
    engine->setStrategy(std::make_unique<NormalStrategy>());

    // ---- 2. Create all 4 bots, each with its own starting Portfolio ----
    std::vector<BotEntry> entries;
    entries.push_back({ std::make_unique<MomentumBot>("MomentumBot", STARTING_CASH), Portfolio(STARTING_CASH) });
    entries.push_back({ std::make_unique<RandomBot>("RandomBot", STARTING_CASH),     Portfolio(STARTING_CASH) });
    entries.push_back({ std::make_unique<ValueBot>("ValueBot", STARTING_CASH, 100.0), Portfolio(STARTING_CASH) });
    entries.push_back({ std::make_unique<PanicBot>("PanicBot", STARTING_CASH),       Portfolio(STARTING_CASH) });

    // ---- 3. Hook up the dashboard ----
    DashboardObserver dash; // writes to dashboard/market_data.json by default
    engine->subscribe(&dash);

    // ---- 4. Helper: after every tick, let each bot decide + trade, then
    //         tell the dashboard the fresh portfolio values ----
    auto runBotsAndUpdateDashboard = [&](bool crashActive) {
        double price = engine->getCurrentPrice();
        std::vector<BotSnapshot> snapshots;

        for (auto& entry : entries) {
            Action action = entry.bot->decideAction(price);

            if (action == Action::BUY) {
                entry.portfolio.buy(STOCK_NAME, SHARES_PER_TRADE, price);
                // If this fails (not enough cash), buy() just returns false —
                // we don't crash, the bot simply couldn't afford it this time.
            } else if (action == Action::SELL) {
                entry.portfolio.sell(STOCK_NAME, SHARES_PER_TRADE, price);
                // Same idea — fails quietly if the bot doesn't hold enough shares.
            }
            // HOLD does nothing.

            double value = entry.portfolio.getTotalValue(price);
            snapshots.push_back({ entry.bot->getName(), value });
        }

        dash.updateBots(snapshots);
        dash.setCrashActive(crashActive);
    };

    // ---- 5. Run the normal market ----
    std::cout << "--- Normal market ---\n";
    for (int i = 0; i < 15; i++) {
        runBotsAndUpdateDashboard(false); // decide + trade BEFORE the price moves again
        engine->tick();                    // advance price, notify dashboard
    }

    // ---- 6. Trigger a crash, live ----
    std::cout << "--- Crash triggered ---\n";
    engine->setStrategy(std::make_unique<CrashStrategy>());
    for (int i = 0; i < 6; i++) {
        runBotsAndUpdateDashboard(true);
        engine->tick();
    }

    // ---- 7. Final leaderboard ----
    double finalPrice = engine->getCurrentPrice();
    std::cout << "\n=== FINAL RESULTS (price: " << finalPrice << ") ===\n";
    std::cout << std::fixed << std::setprecision(2);
    for (auto& entry : entries) {
        double value = entry.portfolio.getTotalValue(finalPrice);
        std::cout << std::setw(12) << entry.bot->getName()
                  << "  ->  Rs " << value << "\n";
    }

    return 0;
}