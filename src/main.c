#include <include/ecs_admin.h>

int main(int argc, char *argv[]) {

    /* Instantiate the world */
    EcsWorld *world = ecs_init();

    /* Import admin system and components. When instantiated, the EcsAdmin
     * component will create EcsHttpServer and EcsHttpEndpoint entities that
     * describe the admin web application */
    ECS_IMPORT(world, EcsSystemsAdmin, 0);

    /* Import the Civetweb HTTP server systems. These systems listen for the
     * EcsHttpServer and EcsHttpEndpoint components, and actually instantiate
     * the server which listens for and forwards the requests. */
    ECS_IMPORT(world, EcsSystemsCivetweb, 0);

    /* Create a new entity with the EcsAdmin component and initialize it */
    ecs_set(world, 0, EcsAdmin, {.port = 9090});

    /* Set a target FPS (optional). Without this line the main loop would run as
     * fast as possible, consuming a lot of CPU. By setting a target FPS, the
     * ecs_progress operation will automatically insert sleeps if it is running
     * too fast. */
    ecs_set_target_fps(world, 60);

    /* Enable system monitoring (optional). This adds overhead as reflecs measures
     * how much time is spent in each system. By default this is turned off.
     * It is possible to turn this setting on or off in the admin web
     * application on the performance panel. */
    ecs_measure_system_time(world, true);

    /* Main loop. Run all the systems that have been imported and are active */
    while ( ecs_progress(world, 0));

    /* While the application is running, open http://localhost:9090 to view
     * the web application. */

    /* Cleanup */
    return ecs_fini(world);
}
