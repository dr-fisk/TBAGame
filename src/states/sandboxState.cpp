#include "states/sandboxState.hpp"
#include "renderer/renderer2D.hpp"
#include "renderer/renderCommand.hpp"

SandboxState::SandboxState(const std::stack<std::shared_ptr<State>>& crStates) : State(crStates)
{
  const int num_sprites = 220;
  mSprites.reserve(num_sprites);

  Transform trans;
  trans.setScale({2.0f, 2.0f});
  trans.setPos({1.0f, 1.0f});
  for(size_t i = 0; i < num_sprites; i++)
  {
    mSprites.push_back(Sprite());
    mSprites[i].setTransform(trans);
    mSprites[i].setColor(lg::Blue);

    trans += glm::vec2{2, 0};
  }

  mCam = std::make_shared<OrthCamera>(0, 1920, 1080, 0);
}

void SandboxState::fixedUpdate(const std::shared_ptr<RenderTarget>& crpTarget, const double cDeltaTime)
{
  Event tempEvent;

  // while(crpTarget->pollEvent(tempEvent))
  // {
  //   switch(tempEvent.Type)
  //   {
  //     case Event::EventType::WindowResize:
  //     {
  //       // Viewport needs to be updated on window resize if you want viewport to be same as windowsize
  //       mCam->setProjection(tempEvent.WindowView.x, tempEvent.WindowView.Width, tempEvent.WindowView.Height, tempEvent.WindowView.y);
  //       glViewport(tempEvent.WindowView.x, tempEvent.WindowView.y, tempEvent.WindowView.Width, tempEvent.WindowView.Height);
  //       // int view[4];
  //       // glGetIntegerv(GL_VIEWPORT, view);
  //       // std::cout << "View: (" << tempEvent.WindowView.x << ", " << tempEvent.WindowView.y << ") " << "(" << tempEvent.WindowView.Width << ", " << tempEvent.WindowView.Height << ")\n";
  //       // std::cout << "View: (" << view[0] << ", " << view[1] << ") " << "(" << view[2] << ", " << view[3] << ")\n";
  //       break;
  //     }
  //     default:
  //       break;
  //   }
  // }
}

void SandboxState::render(const std::shared_ptr<RenderTarget>& crpTarget, const double cDeltaTime)
{
  RenderCommand::clear();
  Renderer2D::beginScene(mCam);
  for(auto& sprite : mSprites)
  {
    sprite.draw();
  }
  Renderer2D::endScene();
}

SandboxState::~SandboxState()
{

}