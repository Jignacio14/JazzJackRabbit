Vagrant.configure('2') do |config|
  (1..1).each do |i|
  config.vm.define "jjr2-host" do |machine|
    machine.vm.box = 'hashicorp/bionic64'
    config.vm.network "forwarded_port", guest: 3500, host:3500
    config.ssh.insert_key = false
    machine.vm.hostname = "jjr2-host"
    machine.vm.provider "virtualbox" do |vb|
      vb.name = "jjr2_#{i}"
      vb.cpus = '4'
      vb.memory = '2048'
      vb.gui = true
    end
    config.vm.provision "shell", path: "provisioning_vagrant.sh"
  end
  end
end
