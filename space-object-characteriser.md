# Space Object Characteriser — Project Summary

A proof-of-concept and learning project: infer the physical properties and origin of poorly characterised space objects from public tracking data, then verify the estimates against known ground truth.

## Goal

Given an object's orbit history, estimate:

1. **Area-to-mass ratio (A/m)** from drag and solar radiation pressure signatures (first milestone)
2. **Origin**: parent body and breakup event, by back-propagation (second milestone)
3. **Attitude and material** from photometry (later; public truth data is thin)

Verifying the estimates matters more than accumulating data sources.

## Data sources

| Purpose | Source |
| --- | --- |
| Orbit history, catalogue, RCS size class | Space-Track (GP/TLE history, SATCAT, decay/TIP); CelesTrak; TraCSS later |
| Ground truth labels | ESA DISCOS (mass, dimensions, shape), GCAT, UNOOSA registry |
| Spin and attitude | Mini-MegaTORTORA, IAU CPS SatHub, SLR via ILRS/CDDIS |
| Force-model inputs | F10.7/Ap (CelesTrak, NOAA SWPC), JB2008 indices, IERS EOP, JPL ephemerides |
| Population priors | ESA MASTER, NASA ORDEM |

**Minimum viable dataset:** Space-Track GP history + SATCAT, DISCOS labels, space weather indices.

**Constraints:** genuinely uncorrelated tracks are mostly withheld, so "unknown" means poorly characterised catalogued objects or simulated UCTs. TLEs carry km-level errors, and B\* absorbs mismodelling, so A/m estimates need careful uncertainty handling.

## Verification plan

1. **Synthetic truth:** propagate objects with known A/m, shape and spin in a high-fidelity model. Generate pseudo-observations and fit SGP4 TLEs to them, as the catalogue does. Score bias and uncertainty calibration (NEES, interval coverage), not only point error.
2. **Blind tests on real objects:** strip identity from DISCOS-labelled objects and predict their properties.
   - Calibration spheres and SLR satellites (LAGEOS, LCS): precise A/m
   - Well-documented rocket bodies (SL-16, CZ upper stages)
   - Known breakup fragments (Fengyun-1C, Cosmos 2251, Iridium 33): origin attribution
   - Envisat: published spin-rate truth
   - Split train/test by launch or breakup family, to avoid leakage between near-identical fragments.
3. **Independent cross-checks:** spin vs SLR or published lightcurves; size vs SATCAT RCS class.

## Custom C++ propagator

This is the dynamics core, used both to generate synthetic truth and to estimate A/m. It absorbs the two-body + J2 project from the C++ portfolio plan.

**Build ourselves:**

- Integrators: RK4, then adaptive RK78/DOP853
- Modular force models: two-body → J2 → EGM2008 (~20×20) → drag → SRP (with eclipse) → Sun/Moon
- STM and partials w.r.t. Cd·A/m (variational equations)
- Estimator: batch least squares, then EKF

**Reuse:** Vallado SGP4, SOFA/ERFA frames, NRLMSISE-00/JB2008, CSPICE + DE kernels.

**Propagator verification:** energy and angular momentum conservation; analytic J2 secular rates; head-to-head with Orekit or GMAT (target: metres over a day); Vallado SGP4 test cases.

**Main risk:** the propagator absorbs the whole project. Timebox it: two-body + J2 + drag + RK78 is enough to start the A/m work.

## Roadmap

| Phase | Content | Status |
| --- | --- | --- |
| Part 1 | Toolchain, CMake + Catch2, Vec3, two-body RK4 with energy and convergence tests | Walkthrough written; in progress |
| Part 2 | Kepler elements ↔ Cartesian, J2 + RAAN-drift test, `ForceModel` interface, adaptive integrator | Next |
| Part 3 | Drag, space weather inputs, SRP, frames (SOFA), SGP4 integration | — |
| Part 4 | STM, batch least-squares A/m estimation, synthetic-truth validation | — |
| Part 5 | Real-data blind tests (DISCOS), then breakup origin attribution | — |
| Later | Photometric attitude and material characterisation | — |

## Engineering conventions

- C++20, CMake + Ninja, Catch2, VS Code
- Google style via clang-format/clang-tidy, plus `bugprone-*`, `cert-*`, `cppcoreguidelines-*` and `hicpp-*` checks
- NASA/JPL Power of 10 where it fits a ground tool; MISRA-informed, with no claim of compliance
- Units: km, s, km/s throughout

## Key references

- Montenbruck & Gill, *Satellite Orbits*: force models, integrators, orbit determination
- Vallado, *Fundamentals of Astrodynamics and Applications*: frames, SGP4
