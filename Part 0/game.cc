#include "game.hh"
#include "assert.hh"
using namespace pro2;

Game::Game(int width, int height)
    : mario_({width / 2, 150}, Keys::Space , Keys::Left, Keys::Right),
      mario2_({width / 2 - 30, 150}, 'W', 'A', 'D'), //  0.2, 0.3
      platforms_{
          Platform(100, 300, 200, 211),
          Platform(0, 200, 250, 261),
          Platform(250, 400, 150, 161),
      },
      finished_(false), paused_(false) {
    assert(width > 0 && height > 0, "L'amplada i l'alcada del joc han de ser positives.");
    for (int i = 1; i < 20; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 161));
    }
}

void Game::process_keys(pro2::Window& window) {
    if (window.was_key_pressed(Keys::Escape)) {
        finished_ = true;
        return;
        //Keys::Escape  
    }
    else if (window.was_key_pressed('P')){
        paused_ = !paused_;
    }
}

void Game::update_objects(pro2::Window& window) {
    mario_.update(window, platforms_);
    // 0.2
    mario2_.update(window, platforms_);
}

void Game::update_camera(pro2::Window& window) {
    const Pt pos = mario_.pos();
    const Pt cam = window.camera_center();

    //0.4
    int dx = pos.x - cam.x;
    int dy = pos.y - cam.y;
    
    window.move_camera({dx, dy});
}

void Game::update(pro2::Window& window) {
    if (not paused_)
    update_objects(window);
    update_camera(window);
}

void Game::paint(pro2::Window& window) {
    window.clear(sky_blue);
    /*
    //0.7
    Pt centre = window.camera_center();
    Rect r = {centre.x - 20, centre.y - 20, centre.x + 20, centre.y + 20};
    paint_rect(window, r, pro2::yellow);
    */
    

    for (const Platform& p : platforms_) {
        p.paint(window);
    }
    mario_.paint(window);
    //0.2
    mario2_.paint(window);

    //0.5
    Rect camera = window.camera_rect();
    paint_hline(window,camera.left,camera.right,camera.top, pro2::green );
    paint_hline(window,camera.left,camera.right,camera.bottom - 1, pro2::green );
    paint_vline(window, camera.left, camera.top, camera.bottom, pro2::green);
    paint_vline(window, camera.right -1, camera.top, camera.bottom, pro2::green);

    //0.8
    if (window.frame_count() % 75 < 25){
        Pt centre = window.camera_center();
        Rect r = {centre.x - 20, centre.y - 20, centre.x + 20, centre.y + 20};
        paint_rect(window, r, pro2::yellow);
    }
}