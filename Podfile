
target 'SF_GaoDeMAP' do
    
    pod 'AFNetworking'
#    pod 'AMap3DMap'#AMapNavi包含AMap3DMap
    pod 'AMapSearch' #搜索服务SDK
    pod 'AMapLocation'
    pod 'AMapNavi'#这个要放到其他高德sdk后
    pod 'JZLocationConverter'#gps纠偏
end

post_install do |installer|
  installer.pods_project.targets.each do |target|
    target.build_configurations.each do |config|
      config.build_settings['ARCHS'] = 'arm64'
    end
  end
end
