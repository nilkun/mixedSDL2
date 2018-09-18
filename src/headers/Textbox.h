Textbox::Textbox;

SDL_Rect position;

void update();

void render();
void onClick();

// check click in viewport

click(SDL_Point* mouse)
{
    if(mouse.x > outline.x 
        && mouse.x < outline.w + outline.x
        && mouse.y > outline.y
        && mouse y < outline.y + outline.h)
    {
        // Viewport has been clicked

        // Normalize
        int mouseX = mouse.x - outline.x;
        int mouseY = mouse.y - outline.y;
        for(auto const& item : items)
        {
            if(mouseX > item.position.x 
                && mouseX < item.position.x + item.position.w
                && mouseY > item.position.y
                && mouseY < item.position.y + item.position.h)
            {
                item.click();
            }
        }
    }
}