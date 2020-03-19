ICONS_BUILDPATH := build
APP_ICON_PATH := .
CONVERT := convert # This tool may conflict with the one provided by Microsoft. Use an absolute path is so

build-icon: ## Build the Windows's application icon
	mkdir -p $(ICONS_BUILDPATH)
	# For Windows icons we need the `convert` tool provided by "Imagemagick"
	$(CONVERT) "$(APP_ICON_PATH)/pokem.png" -resize 16x16 "$(ICONS_BUILDPATH)/appIcon_1.png"
	$(CONVERT) "$(APP_ICON_PATH)/pokem.png" -resize 24x24 "$(ICONS_BUILDPATH)/appIcon_2.png"
	$(CONVERT) "$(APP_ICON_PATH)/pokem.png" -resize 32x32 "$(ICONS_BUILDPATH)/appIcon_3.png"
	$(CONVERT) "$(APP_ICON_PATH)/pokem.png" -resize 48x48 "$(ICONS_BUILDPATH)/appIcon_4.png"
	$(CONVERT) "$(APP_ICON_PATH)/pokem.png" -resize 64x64 "$(ICONS_BUILDPATH)/appIcon_5.png"
	$(CONVERT) "$(APP_ICON_PATH)/pokem.png" -resize 96x96 "$(ICONS_BUILDPATH)/appIcon_6.png"
	$(CONVERT) "$(APP_ICON_PATH)/pokem.png" -resize 128x128 "$(ICONS_BUILDPATH)/appIcon_7.png"
	$(CONVERT) "$(APP_ICON_PATH)/pokem.png" -resize 256x256 "$(ICONS_BUILDPATH)/appIcon_8.png"
	$(CONVERT) "$(APP_ICON_PATH)/pokem.png" -resize 512x512 "$(ICONS_BUILDPATH)/appIcon_9.png"
	$(CONVERT) "$(ICONS_BUILDPATH)/appIcon_*.png" "$(APP_ICON_PATH)/pokem.ico"

# 	mkdir -p $(ICONSET)
# 	# For macOS icons we will use the `sips` and `iconutil` tools as provided by Apple
# 	$(SIPS) -z 16 16 "$(APP_ICON_PATH)/pokem.png" --out "$(ICONSET)/icon_16x16.png"
# 	$(SIPS) -z 32 32 "$(APP_ICON_PATH)/pokem.png" --out "$(ICONSET)/icon_16x16@2x.png"
# 	$(SIPS) -z 32 32 "$(APP_ICON_PATH)/pokem.png" --out "$(ICONSET)/icon_32x32.png"
# 	$(SIPS) -z 64 64 "$(APP_ICON_PATH)/pokem.png" --out "$(ICONSET)/icon_32x32@2x.png"
# 	$(SIPS) -z 128 128 "$(APP_ICON_PATH)/pokem.png" --out "$(ICONSET)/icon_128x128.png"
# 	$(SIPS) -z 256 256 "$(APP_ICON_PATH)/pokem.png" --out "$(ICONSET)/icon_128x128@2x.png"
# 	$(SIPS) -z 256 256 "$(APP_ICON_PATH)/pokem.png" --out "$(ICONSET)/icon_256x256.png"
# 	$(SIPS) -z 512 512 "$(APP_ICON_PATH)/pokem.png" --out "$(ICONSET)/icon_256x256@2x.png"
# 	$(SIPS) -z 512 512 "$(APP_ICON_PATH)/pokem.png" --out "$(ICONSET)/icon_512x512.png"
# 	$(SIPS) -z 1024 1024 "$(APP_ICON_PATH)/pokem.png" --out "$(ICONSET)/icon_512x512@2x.png"
# 	$(ICONUTIL) --convert icns --output "$(APP_ICON_PATH)/appIcon.icns" "$(ICONSET)"

clean:
	rm -rf $(ICONS_BUILDPATH)