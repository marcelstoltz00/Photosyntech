# State Transitions — Values & Checks

Assumptions
- Time unit: days. grow() called once per day and increments age by 1.
- Ranges: health, waterLevel, sunExposure ∈ [0,100].
- Seasons: Spring, Summer, Autumn, Winter (affect water usage).
- Clamp health/water/sunExposure to [0,100] after any update.

## Season multipliers (water usage)
| Season  | Multiplier |
|---------|------------|
| Spring  | 0.9        |
| Summer  | 1.3        |
| Autumn  | 1.0        |
| Winter  | 0.8        |

## Overview table (per-state parameters)

| Parameter / State | Seed | Vegetative | Mature | Dead |
|-------------------|------|------------|--------|------|
| Acceptable age range (days) | 0 — 6 | 7 — 29 | 30 — 119 | ≥ 120 (terminal) |
| Acceptable health range | 30 — 100 | 40 — 100 | 30 — 100 | 0 |
| Acceptable water range | 40 — 100 | 25 — 100 | 30 — 100 | 0 |
| Acceptable sunExposure range | 20 — 100 | 40 — 100 | 40 — 100 | 0 |
| Per-day baseline water usage (units/day) | 6 | 10 | 8 | 0 |
| Per-day health gain if minima met (units/day) | +4 | +3 | +1 | 0 |
| Min water required for daily growth check | 40 | 30 | 30 | 0 |
| Min sunExposure required for daily growth check | 20 | 40 | 40 | 0 |
| Transition target | Vegetative | Mature | Dead | (none) |
| Transition condition (single-tick) | age ≥ 7 AND health ≥ 50 AND water ≥ 50 AND sunExposure ≥ 30 | age ≥ 30 AND health ≥ 60 AND water ≥ 40 AND sunExposure ≥ 50 | age ≥ 120 OR health ≤ 0 | — |
| On successful transition: water reset | 25 | 40 | 0 | 0 |
| On successful transition: health reset/minimum | max(current,50) | max(current,60) | 0 | 0 |
| On successful transition: sunExposure reset | 50 | 60 | 0 | 0 |
| Notes | grow(): apply baseline water usage * season multiplier, then if water & sun meet minima add health gain, then check transition | same flow as Seed but with vegetative params | same flow; if transition to Dead set all to 0 | terminal — no changes |

## Explicit per-state grow() checks (order of operations)
1. Increment plant.age by 1.
2. Compute water usage: usage = round(baseline_water_usage * season_multiplier).
3. Update water: waterLevel = clamp(waterLevel - usage, 0, 100).
4. If waterLevel >= minWaterForGrowth AND sunExposure >= minSunForGrowth then health = clamp(health + healthGainIfGood, 0, 100).
   - Otherwise health unchanged (no consecutive-day penalties in this simplified model).
5. Check transition conditions for the current state (single-tick checks listed above).
   - If condition met, set new state and apply resets:
     - Seed → Vegetative: water := 25, health := max(health,50), sunExposure := 50
     - Vegetative → Mature: water := 40, health := max(health,60), sunExposure := 60
     - Mature → Dead: health := 0, water := 0, sunExposure := 0
6. No reverse transitions. Dead is terminal.

## Quick reference — transition conditions only
| From -> To | Condition |
|------------|-----------|
| Seed -> Vegetative | age ≥ 7 AND health ≥ 50 AND water ≥ 50 AND sunExposure ≥ 30 |
| Vegetative -> Mature | age ≥ 30 AND health ≥ 60 AND water ≥ 40 AND sunExposure ≥ 50 |
| Mature -> Dead | age ≥ 120 OR health ≤ 0 |
| Dead -> (none) | n/a |

## Example numeric day flow (Seed, Spring)
- baseline water usage = 6; Spring multiplier = 0.9 → usage = round(5.4) = 5
- waterLevel := waterLevel - 5
- if waterLevel ≥ 40 and sunExposure ≥ 20: health += 4
- if age becomes ≥ 7 and health ≥ 50 and waterLevel ≥ 50 and sunExposure ≥ 30 → transition to Vegetative and apply resets