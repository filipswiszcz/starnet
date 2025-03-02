# scrap the data from sky-map
# categorize by constellations (caching stars from current constellation)
# find pattern with some star, from which star's pos can be found (sphere coordinate system)
# if i have one pos, then i can search for other stars (brighter spots on frame with certain characterictics)

# i can also take pos of device and current time/date

import pygame
import subprocess


WIDTH, HEIGHT = 1920 // 2, 1080 // 2
SURFACE = pygame.HWSURFACE | pygame.DOUBLEBUF | pygame.RESIZABLE

pygame.init()
pygame.mixer.init()
window = pygame.display.set_mode((WIDTH, HEIGHT), SURFACE)
pygame.display.set_caption("Powered by XYCORP Labs")


class Video(pygame.sprite.Sprite):
    FFMPEG_BIN = "/opt/homebrew/bin/ffmpeg"

    def __init__(self, filename, rect, fps=25):
        pygame.sprite.Sprite.__init__(self)
        cmd = [
            self.FFMPEG_BIN,
            "-loglevel", "quiet",
            "-i", filename,
            "-f", "image2pipe",
            "-s", "%dx%d" % (rect.width, rect.height),
            "-pix_fmt", "rgb24",
            "-vcodec", "rawvideo", "-"
        ]
        self.bytes_per_frame = rect.width * rect.height * 3
        self.proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, bufsize=self.bytes_per_frame * 3)
        self.image = pygame.Surface((rect.width, rect.height), pygame.HWSURFACE)
        self.rect = self.image.get_rect()
        self.rect.x = rect.x
        self.rect.y = rect.y
        self.last_at = 0
        self.frame_delay = 1000 / fps
        self.is_video_stopped = False

    def update(self):
        if not self.is_video_stopped:
            tnow = pygame.time.get_ticks()
            if tnow > self.last_at + self.frame_delay:
                self.last_at = tnow
                try:
                    raw_img = self.proc.stdout.read(self.bytes_per_frame)
                    self.image = pygame.image.frombuffer(raw_img, (self.rect.width, self.rect.height), "RGB")
                except:
                    self.image = pygame.Surface((self.rect.width, self.rect.height), pygame.HWSURFACE)
                    self.image.fill((0, 0, 0))
                    self.is_video_stopped = True


def run():
    video = Video("5939440-hd_1920_1080_30fps.mp4", pygame.Rect(0, 0, WIDTH, HEIGHT))
    group = pygame.sprite.Group()
    group.add(video)

    font = pygame.font.Font(pygame.font.get_default_font(), 11)
    text = font.render("SIRIUS", True, (197, 0, 60))

    text_rect = text.get_rect()
    text_rect.topleft = (100, 100)

    rect = pygame.Rect(text_rect.left - 5, text_rect.top - 5, text_rect.width + 2 * 5, text_rect.height + 2 * 5)

    is_running = True
    clock = pygame.time.Clock()
    while is_running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT: is_running = False

        group.update()
        window.fill((0, 0, 0))
        group.draw(window)

        pygame.draw.lines(video.image, (197, 0, 60), False, [(600, 200), (660, 200), (600, 200), (600, 220)])
        pygame.draw.lines(video.image, (197, 0, 60), False, [(600, 220), (660, 220), (660, 200), (660, 220)])

        pygame.draw.rect(window, (197, 0, 60), rect, 1)
        window.blit(text, text_rect.topleft)

        pygame.display.flip()
        clock.tick_busy_loop(30)

    pygame.quit()


if __name__ == "__main__":
    run()