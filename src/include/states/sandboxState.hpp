#ifndef SANDBOX_STATE_HPP
#define SANDBOX_STATE_HPP

#include <vector>

#include "states/state.hpp"
#include "drawable/sprite.hpp"

class SandboxState : public State
{
  public:
    SandboxState(const std::stack<std::shared_ptr<State>>& crStates);
    ~SandboxState();
    void render(const std::shared_ptr<RenderTarget>& crpTarget, const double cDeltaTime) override;
    // virtual void update(const std::shared_ptr<RenderTarget>& crpTarget, const double cDeltaTime);
    void fixedUpdate(const std::shared_ptr<RenderTarget>& crpTarget, const double cDeltaTime) override;
    // virtual void lateUpdate(const std::shared_ptr<RenderTarget>& crpTarget, const double cDeltaTime);
    bool shouldStateExit() override {return false;}
  private:
    std::shared_ptr<OrthCamera> mCam;
    std::vector<Sprite> mSprites;
};

#endif