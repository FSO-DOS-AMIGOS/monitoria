build:
	@echo "\nBuilding Monitoria ...\n"
	@docker build -t monitoria .

run:
	@echo "\nRunning Monitoria ...\n"
	@docker build -t monitoria .
	@(docker run -w /monitoria/src monitoria:latest bash -c "./monitoria")

exec:
	@echo "\nExecuting Monitoria ...\n"
	@(docker run -w /monitoria/src monitoria:latest bash -c "./monitoria")

rm:
	@echo "\nRemoving Monitoria container ...\n"
	@docker rm -f monitoria

rm-network:
	@echo "\nRemoving Monitoria network ...\n"
	@docker network rm monitoria_default

rm-img:
	@echo "\nRemoving Monitoria image ...\n"
	@docker images rmi monitoria
help:
	@echo "\n\t\t\t\tMONITORIA"
	@echo "\n\tmake build - Builds the docker image that contains the app"
	@echo "\tmake run - Runs the previously created docker image and show the output"
	@echo "\tmake rm - Removes the container created by the app"
	@echo "\tmake rm-network - Removes the default network created by the app"
	@echo "\tmake help - Outputs this list\n"
