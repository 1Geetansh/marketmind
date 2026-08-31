# MarketMind — AI Trading Bot Arena

A simulated stock market where four AI trading "bot" personalities compete against each other in real time. Built as an OOP Lab project in C++, demonstrating the Singleton, Strategy, and Observer design patterns alongside core object-oriented principles (encapsulation, inheritance, polymorphism).

A live browser dashboard visualizes the price movement and each bot's portfolio value as the simulation runs.

---

## What it does

Four bots, each with a different trading personality, start with the same cash balance and independently decide whether to buy, sell, or hold as the simulated stock price moves:

- **MomentumBot** — buys when the price is trending up, sells when it's trending down
- **ValueBot** — buys dips below a reference "fair value," sells when the price rises above it
- **PanicBot** — sells everything at the first sign of a price drop, however small
- **RandomBot** — makes random decisions, used as a baseline to show the other strategies aren't just luck

The market runs through a normal trading phase, then a simulated crash, and the dashboard shows all four bots' portfolio values racing against each other live.

---

## Architecture & design patterns

| Pattern / Concept | Where it's used |
|---|---|
| **Singleton** | `MarketEngine` — exactly one market exists at a time |
| **Strategy** | `PriceStrategy` (`NormalStrategy`, `CrashStrategy`, `BullRunStrategy`) — how prices move is swappable at runtime |
| **Observer** | `Observer` interface — bots and the dashboard both subscribe to price updates from `MarketEngine` |
| **Polymorphism** | `Bot` abstract class — each bot subclass implements `decideAction()` differently |
| **Encapsulation** | `Portfolio` — cash and holdings are only modified through `buy()` / `sell()` |

### Core classes

- `MarketEngine` — the central singleton that owns the current price, advances it each "tick," and notifies subscribers
- `Bot` — abstract base class; `MomentumBot`, `ValueBot`, `PanicBot`, `RandomBot` all implement it
- `Portfolio` — tracks one entity's cash and share holdings
- `Stock` — tracks a stock's name, current price, and price history
- `PriceStrategy` — interface for pluggable price-movement behavior
- `Observer` — interface for anything that wants live price updates (bots, dashboard)
- `DashboardObserver` — writes live simulation state to `dashboard/market_data.json` for the frontend to read

---

## Project structure

```
marketmind/
├── include/          # header files (class declarations)
├── src/              # implementation files
│   └── bots/         # the four bot implementations
├── dashboard/         # live browser dashboard (HTML/JS)
├── tests/            # standalone test files for individual components
├── CMakeLists.txt
└── README.md
```

---

## Building and running

Requires CMake (3.10+) and a C++17 compiler.

```bash
git clone https://github.com/1Geetansh/marketmind.git
cd marketmind
mkdir build && cd build
cmake ..
cmake --build .
cd ..
./build/marketmind
```

On Windows, the executable will be under `build/Debug/marketmind.exe`.

The program prints the simulation's progress to the terminal and finishes with a final leaderboard of each bot's ending portfolio value.

---

## Running the live dashboard

The dashboard reads `dashboard/market_data.json`, which the program updates on every tick.

1. In one terminal, start a local server from the `dashboard` folder:
   ```bash
   cd dashboard
   python3 -m http.server 8000
   ```
2. Open `http://localhost:8000/dashboard.html` in your browser
3. In a second terminal, run the simulation from the project root:
   ```bash
   ./build/marketmind
   ```
4. Watch the dashboard update live as the simulation runs — including a crash trigger partway through

---

## Team

A 5-person OOP Lab project, Section B, built as a group.