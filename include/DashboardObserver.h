#pragma once
// DashboardObserver.h
//
// NOT a locked file — safe to add to the repo without asking the team lead.
// It only *implements* the existing Observer interface (from Observer.h),
// it does not change Observer.h, Bot.h, or Portfolio.h in any way.
//
// WHAT THIS DOES:
// Every time MarketEngine::tick() fires a price update, this writes the
// current price (and whatever bot values it's been given) out to
// "dashboard/market_data.json" — the exact file dashboard.html polls.
//
// WHY BOT VALUES ARE PASSED IN MANUALLY (updateBots):
// Bot.h and Portfolio.h don't expose cash/portfolio getters yet, and
// Portfolio.cpp isn't implemented yet. Rather than guess at that API,
// this class just accepts a list of (name, value) pairs from whoever
// calls it. Once Portfolio::getTotalValue() exists, main.cpp (or
// wherever the tick loop lives) can call updateBots() each tick with
// real numbers — no changes needed here.
//
// USAGE EXAMPLE (illustrative — adjust to fit the real tick loop once
// bots + portfolios are wired up; this is intentionally NOT wired into
// the shared main.cpp so it doesn't create a merge conflict):
//
//   DashboardObserver dash;
//   engine->subscribe(&dash);
//
//   // each tick, once bot portfolio values are available:
//   dash.updateBots({
//       {"MomentumBot", momentumBot.getPortfolio().getTotalValue(price)},
//       {"ValueBot",    valueBot.getPortfolio().getTotalValue(price)},
//       {"PanicBot",    panicBot.getPortfolio().getTotalValue(price)},
//       {"RandomBot",   randomBot.getPortfolio().getTotalValue(price)}
//   });
//   dash.setCrashActive(usingCrashStrategy); // true while CrashStrategy is active
//
//   engine->tick(); // triggers onPriceUpdate -> writes market_data.json

#include "Observer.h"
#include <string>
#include <vector>
#include <fstream>

struct BotSnapshot {
    std::string name;
    double value;
};

class DashboardObserver : public Observer {
private:
    std::string outputPath;
    int tickCount = 0;
    bool crashActive = false;
    std::vector<BotSnapshot> bots;

public:
    explicit DashboardObserver(const std::string& path = "dashboard/market_data.json")
        : outputPath(path) {}

    // Call before engine->tick() once real bot values are available.
    void updateBots(const std::vector<BotSnapshot>& latestBots) {
        bots = latestBots;
    }

    // Call whenever a CrashStrategy is active vs. not, so the dashboard
    // can show its crash banner in sync with the real simulation.
    void setCrashActive(bool active) {
        crashActive = active;
    }

    // Called automatically by MarketEngine on every tick() once subscribed.
    void onPriceUpdate(double newPrice) override {
        tickCount++;
        writeJson(newPrice);
    }

private:
    void writeJson(double price) {
        std::ofstream out(outputPath);
        if (!out) {
            // Fails silently on purpose: if the "dashboard" folder doesn't
            // exist yet, or the program can't write there, the dashboard
            // just keeps showing its own demo data instead of crashing
            // your simulation.
            return;
        }

        out << "{\n";
        out << "  \"time\": " << tickCount << ",\n";
        out << "  \"price\": " << price << ",\n";
        out << "  \"crashed\": " << (crashActive ? "true" : "false") << ",\n";
        out << "  \"bots\": [\n";
        for (size_t i = 0; i < bots.size(); i++) {
            out << "    { \"name\": \"" << bots[i].name << "\", \"value\": " << bots[i].value << " }";
            if (i + 1 < bots.size()) out << ",";
            out << "\n";
        }
        out << "  ]\n";
        out << "}\n";
    }
};
