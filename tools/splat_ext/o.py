# Adds `o` segment support to splat
# Original script by mkst, slightly modified for silent-hill-decomp

from typing import Optional
from pathlib import Path

from splat.segtypes.common.lib import CommonSegment
from splat.segtypes.segment import parse_segment_vram

class PSXSegO(CommonSegment):

    def __init__(
        self,
        rom_start: Optional[int],
        rom_end: Optional[int],
        type: str,
        name: str,
        vram_start: Optional[int],
        args: list,
        yaml,
    ):
        super().__init__(
            rom_start,
            rom_end,
            type,
            name,
            vram_start,
            args=args,
            yaml=yaml,
        )

        vram = parse_segment_vram(self.yaml)
        if vram is not None:
            self.vram_start = vram

        if isinstance(yaml, dict):
            self.section = yaml.get("section", ".text")
        else:
            if len(args) > 0:
                self.section = args[0]
            else:
                self.section = ".text"

        self.extract = False

    def get_linker_section(self) -> str:
        return self.section

    def out_path(self) -> Optional[Path]:
        # TODO: "o" segments currently need to use "../../" to access the repo root, as `options.opts.base_path` doesn't seem to work here?
        out_path = Path(f"{self.name}")
        return out_path
