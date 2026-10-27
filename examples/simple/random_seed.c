#include <igraph.h>
#include <stdio.h>

int main(void) {
    igraph_t graph;
    igraph_rng_t rng;
    igraph_rng_t *previous_rng;
    igraph_int_t die_roll;
    igraph_real_t sample;

    igraph_setup();

    /* Initialize and seed a PCG generator. */
    IGRAPH_CHECK(igraph_rng_init(&rng, &igraph_rngtype_pcg32));
    IGRAPH_CHECK(igraph_rng_seed(&rng, 42));

    /* Draw an integer from the inclusive range [1, 6] and a real in [0, 1). */
    die_roll = igraph_rng_get_integer(&rng, 1, 6);
    sample = igraph_rng_get_unif(&rng, 0.0, 1.0);
    printf("Die roll: %lld\n", (long long) die_roll);
    printf("Uniform sample: %.3f\n", (double) sample);

    /* Temporarily use this generator for igraph functions that need randomness. */
    previous_rng = igraph_rng_set_default(&rng);
    IGRAPH_CHECK(igraph_erdos_renyi_game_gnp(&graph, 100, 3.0 / 100,
                                             IGRAPH_UNDIRECTED, IGRAPH_SIMPLE_SW,
                                             IGRAPH_EDGE_UNLABELED));
    igraph_destroy(&graph);

    /* Restore the previous default before destroying the custom generator. */
    igraph_rng_set_default(previous_rng);
    igraph_rng_destroy(&rng);

    return 0;
}
