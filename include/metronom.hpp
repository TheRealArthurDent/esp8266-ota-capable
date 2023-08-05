#pragma once

/**
 * \brief The metronom.
 *
 * A helper class that let's you manage (somewhat) constant durations
 * of your loop() function. Define a cycleDuration and call waitForNextCycle()
 * at the end of your loop.
 * Easy, isn't it? :)
 */
class Metronom
{
public:
    /**
     * \brief Constructor.
     *
     * Description...
     *
     * \param cycleDuration The duration of one cycle of the loop.
     * \param skipMissedCycles
     * \parblock
     * In case a cycle has been missed - due to stuff happening within the loop
     * taking more time than the defined cycle duration - this bool defines
     * whether the missed cycle should be skipped or not.
     * In this case \c true will make metronom's \c waitForNextCycle just wait
     * until the next regular cycle, thereby skipping at least one cycle,
     * whereas \c false will make metronom's \c waitForNextCycle return
     * immediately and thereby trigger the next iteration of the loop in order
     * to make up the delay.
     * \warning Using \c skipMissedCycles = \c false in conjunction with a loop
     * that usually takes more time than \c cycleDuration will lead to a
     * growing delay that can never be made up.
     * \endparblock
     */
    Metronom(int cycleDuration, bool skipMissedCycles = true) : cycleDuration(cycleDuration), skipMissedCycles(skipMissedCycles){};

    /**
     * Blocks until the next cycle starts.
     * Might return immediately if the Metronom has been configured NOT to skip
     * missed cycles ( \c skipMissedCycles = \c false ).
     * See Metronom(int, bool).
     */
    auto waitForNextCycle() -> void;

private:
    Metronom() = default;                  // hide default constructor
    Metronom(Metronom const &);            // hide copy constructor
    Metronom &operator=(Metronom const &); // hide assignment operator.

    int cycleDuration;
    bool skipMissedCycles;
};