void renderTextEditor(unsigned int width, unsigned int height){
    graphics.fillRect(color_rgba(0, 100, 255, 255), 0, 0, width, 40);
    graphics.print(color_rgba(0, 0, 0, 255), "New File", width/2-(3.5*16)+2, 6, 2, 2);
    graphics.print(color_rgba(255, 255, 255, 255), "New File", width/2-(3.5*16), 3, 2, 2);
    graphics.render();
}