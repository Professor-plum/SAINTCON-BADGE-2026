

int g_seed = 0;

void pseudo_random_init(int seed) {
    g_seed = seed;
}

int psuedo_random() {
    // Simple linear congruential generator (LCG) for demonstration
    g_seed = (g_seed * 1664525 + 1013904223) % 0xFFFFFFFF;
    return g_seed;
}