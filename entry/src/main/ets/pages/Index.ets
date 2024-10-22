import {add, discoverDevices} from "Nvwo";
import { hilog } from '@kit.PerformanceAnalysisKit';

@Entry
@Component
struct Index {
  @State message: string = 'Hello Nvwo';

  build() {
    RelativeContainer() {
      Text(this.message)
        .id('HelloWorld')
        .fontSize(50)
        .fontWeight(FontWeight.Bold)
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center },
          middle: { anchor: '__container__', align: HorizontalAlign.Center }
        })
        .onClick(() => {
          hilog.info(0x0000, 'Nvwo', 'Test NAPI 2 + 3 = %{public}d', add(2, 3));
          hilog.info(0x0000, 'Nvwo', 'start discoverDevices', discoverDevices());
        })
    }
    .height('100%')
    .width('100%')
  }
}