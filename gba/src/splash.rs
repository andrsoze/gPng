use agb::{
    display::{
        GraphicsFrame, Palette16, Priority, Rgb15,
        font::{Font, Layout, LayoutSettings, RegularBackgroundTextRenderer},
        tiled::{RegularBackground, RegularBackgroundSize, TileFormat, VRAM_MANAGER},
    },
    include_font,
};

static FONT: Font = include_font!("fnt/ark-pixel-10px-proportional-latin.ttf", 16);

static PALETTE: &Palette16 = {
    let mut colors = [Rgb15::BLACK; 16];
    colors[1] = Rgb15::WHITE;
    &Palette16::new(colors)
};

pub struct SplashScreen {
    bg: RegularBackground,
}

impl SplashScreen {
    pub fn new() -> Self {
        VRAM_MANAGER.set_background_palette(0, PALETTE);

        let mut bg = RegularBackground::new(
            Priority::P0,
            RegularBackgroundSize::Background32x32,
            TileFormat::FourBpp,
        );

        let layout = Layout::new(
            "gPNG",
            &FONT,
            &LayoutSettings::new().with_max_line_length(200),
        );

        // Centre the text on the 240x160 screen
        let mut renderer = RegularBackgroundTextRenderer::new((88, 72), 0);
        for group in layout {
            renderer.show(&mut bg, &group);
        }

        SplashScreen { bg }
    }

    pub fn show(&mut self, frame: &mut GraphicsFrame) {
        self.bg.show(frame);
    }
}
