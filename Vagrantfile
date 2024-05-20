# Use Vagrant configuration object version 2
Vagrant.configure('2') do |config|

  # Establish VM definition with name jjr2-vm
  config.vm.define "jjr2-vm" do |machine|

    # Define base box
    machine.vm.box = 'bento/ubuntu-22.04'

    # Make available port 3500, forward 3500->3500
    config.vm.network "forwarded_port", guest: 3500, host:3500

    # Disable ssh so no ssh key is required to interact with the system
    config.ssh.insert_key = false

    # Define VM internal name
    machine.vm.hostname = "jjr2-vm"

    # Use VirtualBox provider to run the VM with specific resources
    machine.vm.provider "virtualbox" do |vb|
      vb.name = "jjr2-vm"
      vb.cpus = '4'
      vb.memory = '2048' # in MB
      vb.gui = true # will launch VirtualBox UI
      # Set initial VirtualBox window size to 1000x800
      vb.customize ['setextradata', :id, 'GUI/LastGuestSizeHint', '1000,800']
    end

    # Scripts and reloads to perform during provision time
    config.vm.provision "shell", path: "./scripts/provisioning_start_vagrant.sh"
    config.vm.provision :reload # Directive available thanks to vagrant-reload plugin
    config.vm.provision "shell", path: "./scripts/setup_libs.sh"
    config.vm.provision :reload # Directive available thanks to vagrant-reload plugin
    config.vm.provision "shell", path: "./scripts/provisioning_finish_vagrant.sh"
  end
end
