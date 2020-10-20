<h1>Lab 6: Racecars and Pitstops</h1>

DRIVER control:
- DRIVER checks red/green PIT ENTRY LIGHT 
- If light is GREEN, DRIVER can proceed to pit lane
- If light is RED, DRIVER will need to continue racing

Pit stop control:
- If light is RED, this is because:
    1. Pit lane occupied, or
    2. Pit technicians not ready for pit stop
- PIT ENTRY LIGHT controlled by SUPERVISOR technician
- PIT ENTRY LIGHT -> GREEN only when:
    1. All 17 pit technicians indicate READY, and
    2. Pit lane is EMPTY
- When DRIVER enters pit, SUPERVISOR turns PIT ENTRY LIGHT -> RED 
- When DRIVER stops car completely (time delay), the following happens simultaneously:
    1. REFUELLING technician refuels car
    2. VISOR technician wipes visor
    3. DEBRIS technician wipes debris
    4. Two JACKING technicians jack car (FRONT JACK and BACK JACK)
        - After FRONT JACK: 6 technicians replace two wheels in front :
            -  2x FRONT WHEEL NUT technician takes off nut and puts back nut after new wheel
            -  2x FRONT WHEEL REMOVAL technician removes wheel after nut has been removed
            - 2x FRONT WHEEL REFITTING technician holds and puts on wheel after old wheel is removed
        - After BACK JACK: 6 technicians replace two wheels in back:
            -   2x BACK WHEEL NUT technician takes off nut and puts back nut after new wheel
            -  2x BACK WHEEL REMOVAL technician removes wheel after nut has been removed
            - 2x BACK WHEEL REFITTING technician holds and puts on wheel after old wheel is removed 
        - Sequence of events: Nut off -> old wheel removed -> new wheel replaced -> nut back 
- After both FRONT nuts are in, FRONT JACKING technicians lower jacks
- After both BACK nuts are in, BACK JACKING technicians lower jacks
- SUPERVISOR technician waits for:
    1. REFUELLING done
    2. VISOR wiped
    3. DEBRIS cleared
    4. 2x FRONT JACK lowered
    5. 2x BACK JACK lowered
- Then SUPERVISOR turns on PIT EXIT LIGHT for DRIVER to leave pit
- After car leaves pit, PIT EXIT LIGHT turns off
- All technicians prepare for next pitstop and indicate readiness. If all are ready, PIT ENTRY LIGHT turns green.

Do this for ten cars + 20 laps. 
Cars should come into pit stop at least twice during a race. 

Time delays for technician operations, such as time to jack, time to nut. Explore random time variance. 

Driver lap times should vary but not by much because competitive. 

Include time for technician to get tires from stores, refuelling time (~5s), wheel replacement (2-5 seconds). 

Display on console what is happning in real time. Use MOVE_CURSOR. Use mutex to protect the screen.  

Better displays and simulations will have better grades.
    
