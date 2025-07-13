sha256sum scratch_drm | cut -d' ' -f1 | tr -d '\n' > /tmp/hash
objcopy --add-section .hash=/tmp/hash --set-section-flags .hash=noload,readonly scratch_drm scratch_drm_pat
